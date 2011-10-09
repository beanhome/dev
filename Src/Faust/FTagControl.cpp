#include "FTagControl.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "FEvent.h"
#include "FListControl.h"

BEGIN_EVENT_TABLE(FTagControl, wxPanel)
	EVT_LISTBOX(ID_Tag, OnChangeTag)
END_EVENT_TABLE()


FTagControl::FTagControl()
{}

FTagControl::FTagControl(wxWindow *parent, wxWindowID id, const wxString& sLabel)
	: wxPanel()
	, m_pTag(NULL)
{
	Create(parent, id, sLabel);
}

bool FTagControl::Create(wxWindow *parent, wxWindowID id, const wxString& sLabel)
{
	wxPanel::Create(parent, id);

	wxStaticBoxSizer* pSizer = new wxStaticBoxSizer(wxVERTICAL, this, sLabel);
	{
		m_pTag = new FListControl(this, ID_Tag, wxDefaultPosition, wxSize(150, -1)/*, wxArrayString(), wxLB_MULTIPLE*/);
		pSizer->Add(m_pTag, 0, 0, 0);
	}

	SetSizeHints(160, -1, 160, -1);
	SetSizerAndFit(pSizer);
	Layout();

	UpdateTagList();

	return true;
}


void FTagControl::ClearSelection()
{
	m_pTag->DeselectAll();
}

//ESelectState FTagControl::GetSelectState(const string& sName) const
//{
//	return m_pTag->GetSelectState(sName);
//}


void FTagControl::SetSelection(const wxString& sTag, bool bSelect)
{
	int id = m_pTag->FindString(sTag);
	if (id != wxNOT_FOUND)
		m_pTag->SetSelection(id, bSelect);
}

void FTagControl::SetSelection(const string& sTag, bool bSelect)
{
	SetSelection(wxString(sTag.c_str(), wxConvISO8859_1), bSelect);
}

void FTagControl::SetSelection(const wxString& sTag, ESelectState eSelect)
{
	int id = m_pTag->FindString(sTag);
	if (id != wxNOT_FOUND)
		m_pTag->SetSelection(id, eSelect);
}

void FTagControl::SetSelection(const string& sTag, ESelectState eSelect)
{
	SetSelection(wxString(sTag.c_str(), wxConvISO8859_1), eSelect);
}


void FTagControl::Save(FEvent& oEvent) const
{
	oEvent.ClearTags();
	for (uint i=0 ; i<m_pTag->GetCount() ; ++i)
	{
		if (m_pTag->IsSelected(i))
			oEvent.AddTags(string(m_pTag->GetString(i).mb_str(wxConvISO8859_1)));
	}
}

void FTagControl::Load(const FEvent& oEvent)
{
	for (uint i=0 ; i<m_pTag->GetCount() ; ++i)
	{
		m_pTag->SetSelection(i, oEvent.IsTagged(string(m_pTag->GetString(i).mb_str(wxConvISO8859_1))));
	}
}

void FTagControl::ApplyModif(FEvent& oEvent)
{
	SelectMap aSelectMap;
	m_pTag->GetSelectList(aSelectMap);
	oEvent.ApplyTagModif(aSelectMap);
}


void FTagControl::UpdateTagList()
{
	m_pTag->Clear();

	PGresult* pResult;
	string SQuery = FQ_ALLTAGS;
	if (FApp::s_oSQLClient.Query(SQuery, &pResult))
	{
		int iTuplesCount = PQntuples(pResult);
		for (int i=0 ; i<iTuplesCount ; ++i)
		{
			wxString sTag = wxString(PQgetvalue(pResult, i, 0), wxConvISO8859_1);
			m_pTag->Append(sTag);
		}

		m_pTag->GetSizer()->Fit(m_pTag);
		m_pTag->Layout();
		GetSizer()->Fit(this);
		Layout();
	}
	FApp::s_oSQLClient.Clear(pResult);
}

void FTagControl::GetTag(vector<string>& aTag) const
{
	aTag.clear();

	for (uint i=0 ; i<m_pTag->GetCount() ; ++i)
	{
		if (m_pTag->IsSelected(i))
			aTag.push_back(string(m_pTag->GetString(i).mb_str(wxConvISO8859_1)));
	}
}

string FTagControl::GetJoinQuery() const
{
	vector<string> aTag;
	GetTag(aTag);

	string sQuery;
	if (aTag.size() > 0)
	{
		sQuery += FQ_EVENT_JOIN_TAG_BEGIN;

		for (uint i=0 ; i<aTag.size() ; ++i)
		{
			sQuery += (i == 0 ? "WHERE " : "OR ");
			sQuery += FormatString(FQ_EVENT_JOIN_TAG, aTag[i].c_str());
		}

		sQuery += FQ_EVENT_JOIN_TAG_END;
	}

	return sQuery;
}



void FTagControl::OnChangeTag(wxCommandEvent& event)
{
}