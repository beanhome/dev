#include "IBFactDef.h"
#include "IBFact.h"
#include "IBPlanner.h"
#include "World/IBObject.h"

IBFactDef::IBFactDef(const string& name,IBPlanner* pPlanner)
	: m_sName(name)
	, m_pPlanner(pPlanner)
{
	const char* prefix = "IBFactDef_";
	const uint len = strlen(prefix);
	uint offset = (strncmp(name.c_str(), prefix, len) == 0 ? len : 0);

	m_sName = name.c_str() + offset;
}

IBFactDef::~IBFactDef()
{

}

const string& IBFactDef::GetName() const
{
	return m_sName;
}

uint IBFactDef::GetDegree() const
{
	return m_aVarNames.size();
}

const string& IBFactDef::GetVariableName(uint i) const
{
	static string empty_string;

	ASSERT(i < m_aVarNames.size());

	if (i < m_aVarNames.size())
		return m_aVarNames[i];

	return empty_string;
}


void IBFactDef::AddVariable(const string& name)
{
	m_aVarNames.push_back(name);
}

class IBFact* IBFactDef::Instanciate(bool bInverted) const
{
	return Instanciate(bInverted, nullptr);
}

class IBFact* IBFactDef::Instanciate(bool bInverted, class IBNode* pNode) const
{
	vector<IBObject> aVariables(GetDegree(), IBObject());
	return Instanciate(bInverted, pNode, aVariables);
}

IBFact* IBFactDef::Instanciate(bool bInverted, IBNode* pNode, const vector<IBObject>& aVariables) const
{
	return m_pPlanner->InstanciateFact(this, bInverted, aVariables, pNode);
}

bool IBFactDef::HasSameVariables(const class IBFact* pA, const class IBFact* pB) const
{
	ASSERT(pA != nullptr && pB != nullptr);
	ASSERT(pA->GetFactDef() == this && pB->GetFactDef() == this);
	ASSERT(pA->GetVariables().size() == GetDegree() && pB->GetVariables().size() == GetDegree());

	for (VarMap::const_iterator itA = pA->GetVariables().begin(), itB = pB->GetVariables().begin(); itA != pA->GetVariables().end() && itB != pB->GetVariables().end(); ++itA, ++itB)
	{
		if (itA->second != itB->second)
			return false;
	}

	return true;
}

