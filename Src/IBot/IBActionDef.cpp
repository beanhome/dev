#include "IBActionDef.h"
#include "IBPlanner.h"


IBActionDef::IBActionDef(IBPlanner* pPlanner)
	: m_pPlanner(pPlanner)
{

}

IBActionDef::~IBActionDef()
{

}

void IBActionDef::AddPreCondition(const string& name)
{
	IBFactDef* pFact = m_pPlanner->GetFactDef(name);

	if (pFact != NULL)
		m_aPreCondDef.push_back(pFact);
}

void IBActionDef::AddPostCondition(const string& name)
{
	IBFactDef* pFact = m_pPlanner->GetFactDef(name);

	if (pFact != NULL)
		m_aPostCondDef.push_back(pFact);
}
