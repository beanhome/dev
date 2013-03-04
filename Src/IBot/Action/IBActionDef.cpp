#include "IBActionDef.h"
#include "IBPlanner.h"
#include "IBAction.h"


IBActionDef::IBActionDef(const string& name, IBPlanner* pPlanner)
	: m_sName(name)
	, m_pPlanner(pPlanner)
{
	const char* prefix = "IBActionDef_";
	const uint len = strlen(prefix);
	uint offset = (strncmp(name.c_str(), prefix, len) == 0 ? len : 0);

	m_sName = name.c_str() + offset;
}

IBActionDef::~IBActionDef()
{

}

void IBActionDef::AddVariable(const char* name)
{
	m_aVariable.push_back(name);
}

void IBActionDef::AddPreCondition(const char* name, ...)
{
	IBFactDef* pFact = m_pPlanner->GetFactDef(name);

	assert(pFact != NULL);

	if (pFact != NULL)
	{
		uint n = pFact->GetDegree();

		va_list vl;
		va_start(vl, name);

		FactCondDef oCond(pFact);

		for (uint i=0 ; i<n ; ++i)
		{
			char* arg = va_arg(vl, char*);
			oCond.AddVariable(arg);
		}

		m_aPreCondDef.push_back(oCond);

		va_end(vl);
	}
}

void IBActionDef::AddPostCondition(const char* name, ...)
{
	IBFactDef* pFact = m_pPlanner->GetFactDef(name);

	assert(pFact != NULL);

	if (pFact != NULL)
	{
		uint n = pFact->GetDegree();

		va_list vl;
		va_start(vl, name);

		FactCondDef oCond(pFact);

		for (uint i=0 ; i<n ; ++i)
		{
			char* arg = va_arg(vl, char*);
			oCond.AddVariable(arg);
		}

		m_aPostCondDef.push_back(oCond);

		va_end(vl);
	}
}

IBAction* IBActionDef::Instanciate(IBFact* pPostCond1)
{
	// Instantiation
	IBAction* pAction = m_pPlanner->InstanciateAction(this, pPostCond1);

	// Insert of the post condition
	for (uint i=0 ; i<m_aPostCondDef.size() ; ++i)
	{
		const FactCondDef& oPostCondDef = m_aPostCondDef[i];

		if (oPostCondDef.m_pFactDef == pPostCond1->GetFactDef())
		{
			pAction->AddPostCond(i, pPostCond1);
			break;
		}
	}

	// Resolve unfilled pre cond variable
	pAction->SpreadPreCondVariable();

	return pAction;
}

void IBActionDef::Print(const IBAction::VarMap& aUserData, int tab) const
{
	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s \n", m_sName.c_str());
}

