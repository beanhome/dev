#include "IBGoal.h"
#include "World/IBObject.h"



IBGoal::IBGoal(const char* name)
	: m_sName(name)
{
}

IBGoal::IBGoal(const char* name, IBObject* pUserData)
	: m_sName(name)
{
	m_aUserData.push_back(pUserData);
}

IBGoal::IBGoal(const char* name, IBObject* pUserData1, IBObject* pUserData2)
	: m_sName(name)
{
	m_aUserData.push_back(pUserData1);
	m_aUserData.push_back(pUserData2);
}

IBGoal::IBGoal(const char* name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3)
	: m_sName(name)
{
	m_aUserData.push_back(pUserData1);
	m_aUserData.push_back(pUserData2);
	m_aUserData.push_back(pUserData3);
}


IBGoal::IBGoal(const string& name)
	: m_sName(name)
{
}

IBGoal::IBGoal(const string& name, IBObject* pUserData)
	: m_sName(name)
{
	m_aUserData.push_back(pUserData);
}

IBGoal::IBGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2)
	: m_sName(name)
{
	m_aUserData.push_back(pUserData1);
	m_aUserData.push_back(pUserData2);
}

IBGoal::IBGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3)
	: m_sName(name)
{
	m_aUserData.push_back(pUserData1);
	m_aUserData.push_back(pUserData2);
	m_aUserData.push_back(pUserData3);
}

IBGoal::IBGoal(const IBGoal& Original)
	: m_sName(Original.m_sName)
{
	m_aUserData.resize(Original.m_aUserData.size());

	for (uint i=0 ; i<m_aUserData.size() ; ++i)
	{
		m_aUserData[i] = (Original.m_aUserData[i]->IsInstance() ? Original.m_aUserData[i]->Clone() : Original.m_aUserData[i]);
	}
}

IBGoal::~IBGoal()
{
	for (uint i=0 ; i<m_aUserData.size() ; ++i)
	{
		if (m_aUserData[i]->IsInstance() && m_aUserData[i]->GetOwner() == NULL)
			delete m_aUserData[i];
	}
}



string IBGoal::GetData() const
{
	string sData = "(";

	for (uint i=0 ; i<m_aUserData.size() ; ++i)
	{
		sData += m_aUserData[i]->GetData();

		if (i<m_aUserData.size()-1)
			sData += ", ";
	}

	sData += ")";

	return sData;
}
