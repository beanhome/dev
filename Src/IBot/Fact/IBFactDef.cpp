#include "IBFactDef.h"
#include "IBFact.h"
#include "IBPlanner.h"
#include "World/IBObject.h"

IBFactDef::IBFactDef(const string& name, uint iDegree, IBPlanner* pPlanner)
	: m_sName(name)
	, m_iDegree(iDegree)
	, m_pPlanner(pPlanner)
{
	const char* prefix = "IBFactDef_";
	const uint len = strlen(prefix);
	uint offset = (strncmp(name.c_str(), prefix, len) == 0 ? len : 0);

	m_sName = name.c_str() + offset;

	if (m_iDegree == 1)
		AddVariable("Var");
}

IBFactDef::~IBFactDef()
{

}

const string& IBFactDef::GetName() const
{
	return m_sName;
}

uint	 IBFactDef::GetDegree() const
{
	return m_iDegree;
}

const string& IBFactDef::GetVariableName(uint i) const
{
	static string empty_string;

	ASSERT(i < m_iDegree);

	if (i < m_iDegree)
		return m_aVarNames[i];

	return empty_string;
}


void IBFactDef::AddVariable(const string& name)
{
	ASSERT(m_iDegree > 0 && m_aVarNames.size() < m_iDegree);

	m_aVarNames.push_back(name);
}

class IBFact* IBFactDef::Instanciate(bool bInverted) const
{
	return Instanciate(bInverted, nullptr);
}

class IBFact* IBFactDef::Instanciate(bool bInverted, class IBWorldChange* pWorldChange) const
{
	vector<IBObject> aVariables(m_iDegree, IBObject());
	return Instanciate(bInverted, pWorldChange, aVariables);
}

IBFact* IBFactDef::Instanciate(bool bInverted, IBWorldChange* pWorldChange, const vector<IBObject>& aVariables) const
{
	assert(aVariables.size() == m_iDegree);
	return m_pPlanner->InstanciateFact(this, bInverted, aVariables, pWorldChange);
}

bool	 IBFactDef::HasSameVariables(const class IBFact* pA, const class IBFact* pB) const
{
	ASSERT(pA != nullptr && pB != nullptr);
	ASSERT(pA->GetFactDef() == this && pB->GetFactDef() == this);
	ASSERT(pA->GetVariables().size() == m_iDegree && pB->GetVariables().size() == m_iDegree);

	for (VarMap::const_iterator itA = pA->GetVariables().begin(), itB = pB->GetVariables().begin(); itA != pA->GetVariables().end() && itB != pB->GetVariables().end(); ++itA, ++itB)
	{
		if (itA->second != itB->second)
			return false;
	}

	return true;
}

