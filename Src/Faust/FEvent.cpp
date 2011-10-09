#include "FEvent.h"
#include "FApp.h"
#include "FSQLClient.h"
#include "FQuery.h"


FEvent::FEvent()
: m_uId(0)
, m_uParent(0)
, m_bIncomplete(false)
{
}

FEvent::FEvent(uint id)
: m_uId(id)
, m_uParent(0)
, m_bIncomplete(false)
{
}

FEvent::FEvent(PGresult* res, int iTuple, bool bFull)
	: m_uId(0)
	, m_uParent(0)
	, m_bIncomplete(!bFull)
{
	Load(res, iTuple, m_bIncomplete);
}

FEvent::FEvent(const FEvent& src)
	: m_uId(src.m_uId)
	, m_sName(src.m_sName)
	, m_sDescription(src.m_sDescription)
	, m_oDatation(src.m_oDatation)
	, m_aRoles(src.m_aRoles)
	, m_aTags(src.m_aTags)
	, m_uParent(src.m_uParent)
	, m_bIncomplete(src.m_bIncomplete)
{
}

FEvent::~FEvent()
{
}

void FEvent::AddLocation(const FLocation& oLocation)
{
	m_aLocation.push_back(oLocation);
}

void FEvent::AddLocation(const char* str)
{
	FLocation oLocation = FLocation::Parse(str);
	m_aLocation.push_back(oLocation);
}


string FEvent::GetParentIdString() const
{
	if (IsParentNull())
		return string ("NULL");
	else if (m_sParent.length() == 0)
		return FormatString("%d", m_uParent);
	else
		return FormatString("(SELECT id FROM \"Event\" WHERE name = '%s')", m_sParent.c_str());
}


string FEvent::GetRolesString() const
{
	string sRoles;

	if (!m_bIncomplete)
	{
		for (RoleSet::const_iterator it = m_aRoles.begin() ; it != m_aRoles.end() ; ++it)
		{
			if (it != m_aRoles.begin())
				sRoles += ", ";
			sRoles += *it;
		}
	}
	else
	{
		sRoles = "?";
	}

	return sRoles;
}

bool FEvent::IsRole(const string& sRole) const
{
	return (m_aRoles.find(sRole) != m_aRoles.end());
}

void FEvent::ClearRoles()
{
	m_aRoles.clear();
}

void FEvent::AddRoles(const string& sRole)
{
	int begin=0;
	int end=0;

	while(true)
	{
		while (isspace(sRole[begin]) || sRole[begin] == ',') begin++;
		if (sRole[begin] == 0)
			break;

		end = begin + 1;
		while (!isspace(sRole[end]) && sRole[end] != ',' && sRole[end] != 0) ++end;

		m_aRoles.insert(sRole.substr(begin, end-begin));

		if (sRole[end] == 0)
			break;

		begin = end;
	}
}


string FEvent::GetTagsString() const
{
	string sTags;

	if (!m_bIncomplete)
	{
		for (TagSet::const_iterator it = m_aTags.begin() ; it != m_aTags.end() ; ++it)
		{
			if (it != m_aTags.begin())
				sTags += ", ";
			sTags += *it;
		}
	}
	else
	{
		sTags = "?";
	}

	return sTags;
}

bool FEvent::IsTagged(const string& sRole) const
{
	return (m_aTags.find(sRole) != m_aTags.end());
}

void FEvent::ClearTags()
{
	m_aTags.clear();
}

void FEvent::AddTags(const string& sTag)
{
	int begin=0;
	int end=0;

	while(true)
	{
		while (isspace(sTag[begin]) || sTag[begin] == ',') begin++;
		if (sTag[begin] == 0)
			break;

		end = begin + 1;
		while (!isspace(sTag[end]) && sTag[end] != ',' && sTag[end] != 0) ++end;

		m_aTags.insert(sTag.substr(begin, end-begin));

		if (sTag[end] == 0)
			break;

		begin = end;
	}
}

void FEvent::RemTag(const string& sTag)
{
	TagSet::iterator it =  m_aTags.find(sTag);

	if (it != m_aTags.end())
		m_aTags.erase(it);
}

void FEvent::PushTagToSelection(SelectCountTagMap& aTag)
{
	for (TagSet::const_iterator it = m_aTags.begin() ; it != m_aTags.end() ; ++it)
	{
		const string& sTag = *it;

		SelectCountTagMap::iterator found = aTag.find(sTag);
		if (found != aTag.end())
		{
			found->second++;
		}
		else
		{
			aTag.insert(SelectCountTagPair(sTag, 1));
		}
	}
}

void FEvent::ApplyTagModif(const SelectMap& aSelectedTag)
{
	for (TagSet::const_iterator it = m_aTags.begin() ; it != m_aTags.end() ; ++it)
	{
		if (it == m_aTags.begin())
			continue;

		SelectMap::const_iterator sel = aSelectedTag.find(*it);
		if (sel == aSelectedTag.end() || sel->second == EUnselect)
			m_aTags.erase(it--);
	}
	if (m_aTags.begin() != m_aTags.end())
	{
		SelectMap::const_iterator sel = aSelectedTag.find(*m_aTags.begin());
		if (sel == aSelectedTag.end() || sel->second == EUnselect)
			m_aTags.erase(m_aTags.begin());
	}

	for (SelectMap::const_iterator sel = aSelectedTag.begin() ; sel != aSelectedTag.end() ; ++sel)
	{
		if (sel->second == ESelect)
		{
			if (m_aTags.find(sel->first) == m_aTags.end())
				m_aTags.insert(sel->first);
		}
	}
}

void FEvent::PushRoleToSelection(SelectCountRoleMap& aRole)
{
	for (RoleSet::const_iterator it = m_aRoles.begin() ; it != m_aRoles.end() ; ++it)
	{
		const string& sRole = *it;

		SelectCountRoleMap::iterator found = aRole.find(sRole);
		if (found != aRole.end())
		{
			found->second++;
		}
		else
		{
			aRole.insert(SelectCountRolePair(sRole, 1));
		}
	}
}

void FEvent::ApplyRoleModif(const SelectMap& aSelectedRole)
{
	for (RoleSet::const_iterator it = m_aRoles.begin() ; it != m_aRoles.end() ; ++it)
	{
		if (it == m_aRoles.begin())
			continue;

		SelectMap::const_iterator sel = aSelectedRole.find(*it);
		if (sel == aSelectedRole.end() || sel->second == EUnselect)
			m_aRoles.erase(it--);
	}
	if (m_aRoles.begin() != m_aRoles.end())
	{
		SelectMap::const_iterator sel = aSelectedRole.find(*m_aRoles.begin());
		if (sel == aSelectedRole.end() || sel->second == EUnselect)
			m_aRoles.erase(m_aRoles.begin());
	}

	for (SelectMap::const_iterator sel = aSelectedRole.begin() ; sel != aSelectedRole.end() ; ++sel)
	{
		if (sel->second == ESelect)
		{
			if (m_aRoles.find(sel->first) == m_aRoles.end())
				m_aRoles.insert(sel->first);
		}
	}
}

void FEvent::PushLocationToSelection(SelectCountLocMap& aLoc)
{
	for (uint j=0 ; j<GetLocationCount() ; ++j)
	{
		const FLocation& sLoc = GetLocation(j);

		SelectCountLocMap::iterator it = aLoc.find(sLoc);
		if (it != aLoc.end())
		{
			it->second++;
		}
		else
		{
			aLoc.insert(SelectCountLocPair(sLoc, 1));
		}
	}
}


void FEvent::Save()
{
	bool res = true;

	uint iLastId = m_uId;

	FApp::s_oSQLClient.Query("BEGIN");

	if (res) res &= SaveMainInfo();
	if (res) res &= SaveLocation();
	if (res) res &= SaveRoles();
	if (res) res &= SaveTags();

	FApp::s_oEventMap.ChangeId(this, iLastId);

	FApp::s_oSQLClient.Query(res ? "COMMIT" : "ROLLBACK");
}

void FEvent::Load()
{
	assert(m_uId > 0);

	PGresult* pResult;
	string sQuery(FormatString("SELECT * FROM \"Event\" WHERE id = %d ;", m_uId));
	FApp::s_oSQLClient.Query(sQuery.c_str(), &pResult);
	{
		// TODO gerer l'erreur
		assert(PQntuples(pResult) == 1);
		Load(pResult, 0);
	}
	FApp::s_oSQLClient.Clear(pResult);
}


void FEvent::Load(PGresult* pResult, int iTuple, bool bExpress)
{
	m_bIncomplete = bExpress;

	LoadMainInfo(pResult, iTuple);
	LoadLocation();
	LoadRoles();
	LoadTags();
}

bool FEvent::SaveMainInfo()
{
	bool res = true;

	if (m_uId == 0)
	{
		PGresult* pResult;

		string sQuery = "INSERT INTO \"Event\" (name, description";
		if (!m_oDatation.IsNull())
			sQuery += ", datation";
		if (m_uParent > 0)
			sQuery += ", parent";
		sQuery += ") ";

		sQuery += "VALUES ( ";
		sQuery += "$TEXT$" + m_sName + "$TEXT$ ";
		sQuery += ", $TEXT$" + m_sDescription + "$TEXT$ ";
		if (!m_oDatation.IsNull())
			sQuery += ", " + m_oDatation.GetFormated() + " ";
		if (IsParentNull() == false)
			sQuery += GetParentIdString();
		sQuery += ") ";

		sQuery += "RETURNING id, parent;";

		res &= FApp::s_oSQLClient.Query(sQuery, &pResult);
		if (res)
		{
			const char* sRes = PQgetvalue(pResult, 0, 0);
			assert(sRes != NULL);
			m_uId = atoi(sRes);
		}
		else
		{
			wxMessageBox(wxT("Fail to Insert new Event"), wxT("Error"));
		}
		FApp::s_oSQLClient.Clear(pResult);
	}
	else
	{
		PGresult* pResult;

		string sQuery = "UPDATE \"Event\" SET ";
		sQuery += "name = $TEXT$" + m_sName + "$TEXT$ ";
		sQuery += ", description = $TEXT$" + m_sDescription + "$TEXT$ ";
		sQuery += ", datation = " + m_oDatation.GetFormated() + " ";
		sQuery += ", parent = " + GetParentIdString() + " ";
		sQuery += FormatString(" WHERE id = %d", m_uId);
		sQuery += ";";

		res &= FApp::s_oSQLClient.Query(sQuery, &pResult);
		if (!res)
		{
			wxMessageBox(wxT("Fail to Update Event"), wxT("Error"));
		}

		FApp::s_oSQLClient.Clear(pResult);
	}

	return res;
}

bool FEvent::LoadMainInfo(PGresult* pResult, int iTuple)
{
	int col = 0;

	col = PQfnumber(pResult, "id");
	assert(col != -1);
	m_uId = atoi(PQgetvalue(pResult, iTuple, col));

	col = PQfnumber(pResult, "name");
	assert(col != -1);
	m_sName = PQgetvalue(pResult, iTuple, col);

	col = PQfnumber(pResult, "datation");
	assert(col != -1);
	m_oDatation = FDatation::ParseResult(PQgetvalue(pResult, iTuple, col));

	col = PQfnumber(pResult, "description");
	assert(col != -1);
	m_sDescription = PQgetvalue(pResult, iTuple, col);

	col = PQfnumber(pResult, "parent");
	assert(col != -1);
	m_uParent = (PQgetisnull(pResult, iTuple, col) ? 0 : atoi(PQgetvalue(pResult, iTuple, col)));

	return true;
}

bool FEvent::LoadLocation()
{
	bool res = true;

	if (!m_bIncomplete)
	{
		string sQuery = FormatString(FQ_LOCATION, m_uId);

		PGresult* pResult;
		res &= FApp::s_oSQLClient.Query(sQuery, &pResult);
		if (res)
		{
			m_aLocation.clear();
			
			int iTuplesCount = PQntuples(pResult);
			for (int i=0 ; i<iTuplesCount ; ++i)
			{
				m_aLocation.push_back(FLocation(pResult, i));
			}
		}
		FApp::s_oSQLClient.Clear(pResult);
	}
	else
	{
		m_aLocation.clear();
	}

	return res;
}

bool FEvent::SaveLocation()
{
	bool res = true;

	if (!m_bIncomplete)
	{
		string sQuery = FormatString("DELETE FROM \"Event_Location\" WHERE event_id = %d;", m_uId);
		res &= FApp::s_oSQLClient.Query(sQuery);

		sQuery = "INSERT INTO \"Event_Location\" (event_id, location_id) VALUES";
		if (m_aLocation.size() == 0)
		{
			sQuery += FormatString("(%d, 1)", m_uId); // none loc
		}
		for (uint i=0 ; i<m_aLocation.size() ; ++i)
		{
			sQuery += FormatString("(%d, %d)", m_uId, m_aLocation[i].GetKey());
			if (i < m_aLocation.size()-1)
				sQuery += ",";
		}
		sQuery += ";";

		res &= FApp::s_oSQLClient.Query(sQuery);
		if (!res) wxMessageBox(wxT("Fail to save Location"), wxT("Error"));
	}
	
	return res;
}

bool FEvent::LoadRoles()
{
	bool res = true;
	if (!m_bIncomplete)
	{
		string sQuery = FormatString(FQ_KNOWERS, m_uId);

		PGresult* pResult;
		res &= FApp::s_oSQLClient.Query(sQuery, &pResult);
		if (res)
		{
			int iTuplesCount = PQntuples(pResult);

			m_aRoles.clear();
			for (int i=0 ; i<iTuplesCount ; ++i)
			{
				m_aRoles.insert(string(PQgetvalue(pResult, i, 0)));
			}
		}
		FApp::s_oSQLClient.Clear(pResult);
	}
	else
	{
		m_aRoles.clear();
	}

	return res;
}

bool FEvent::SaveRoles()
{
	bool res = true;

	if (!m_bIncomplete)
	{
		string sQuery = FormatString("DELETE FROM \"Event_Role\" WHERE event_id = %d;", m_uId);
		res &= FApp::s_oSQLClient.Query(sQuery);

		if (m_aRoles.size())
		{
			sQuery = "INSERT INTO \"Event_Role\" (event_id, role) VALUES";
			for (RoleSet::iterator it = m_aRoles.begin() ; it != m_aRoles.end() ; ++it)
			{
				if (it != m_aRoles.begin())
					sQuery += ",";
				sQuery += FormatString("(%d, '%s')", m_uId, (*it).c_str());
			}
			sQuery += ";";

			res &= FApp::s_oSQLClient.Query(sQuery);
			if (!res) wxMessageBox(wxT("Fail to save Knowers"), wxT("Error"));
		}
	}

	return res;
}

bool FEvent::LoadTags()
{
	bool res = true;

	if (!m_bIncomplete)
	{
		string sQuery = FormatString(FQ_TAGS, m_uId);

		PGresult* pResult;
		res &= FApp::s_oSQLClient.Query(sQuery, &pResult);
		if (res)
		{
			m_aTags.clear();
			
			int iTuplesCount = PQntuples(pResult);
			for (int i=0 ; i<iTuplesCount ; ++i)
			{
				m_aTags.insert(string(PQgetvalue(pResult, i, 1)));
			}
		}
		FApp::s_oSQLClient.Clear(pResult);
	}
	else
	{
		m_aTags.clear();
	}

	return res;
}

bool FEvent::SaveTags()
{
	bool res = true;

	if (!m_bIncomplete)
	{
		string sQuery = FormatString("DELETE FROM \"Event_Tags\" WHERE event_id = %d;", m_uId);
		res &= FApp::s_oSQLClient.Query(sQuery);

		if (m_aTags.size())
		{
			sQuery = "INSERT INTO \"Event_Tags\" (event_id, tag_id) VALUES ";
			for (TagSet::iterator it = m_aTags.begin() ; it != m_aTags.end() ; ++it)
			{
				if (it != m_aTags.begin())
					sQuery += ",";
				sQuery += FormatString("(%d, (SELECT id FROM \"Tags\" WHERE tag = '%s'))", m_uId, (*it).c_str());
			}
			sQuery += ";";

			res &= FApp::s_oSQLClient.Query(sQuery);
			if (!res) wxMessageBox(wxT("Fail to save Tags"), wxT("Error"));
		}
	}
	
	return res;
}
