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
