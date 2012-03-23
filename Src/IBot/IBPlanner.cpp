#include "IBPlanner.h"

#include "Fact/IBFact.h"
#include "Fact/Def/IBFactDef_True.h"
#include "Fact/Def/IBFactDef_False.h"
#include "Fact/Def/IBFactDef_Bool.h"
#include "Fact/Def/IBFactDef_IsOnTable.h"
#include "Fact/Def/IBFactDef_IsTopOf.h"

#include "Action/Def/IBActionDef_BoolToBool.h"


IBPlanner::IBPlanner()
{
	InitFactLibrary();
	InitActionLibrary();
}

IBPlanner::~IBPlanner()
{
	for (FactSet::iterator it = m_aGoals.begin() ; it != m_aGoals.end() ; ++it)
		delete (*it);
}

#define REGISTER_FACT(a) m_oFactLibrary.RegisterFactDef(#a, new a())

void IBPlanner::InitFactLibrary()
{
	REGISTER_FACT(IBFactDef_True);
	REGISTER_FACT(IBFactDef_False);
	REGISTER_FACT(IBFactDef_Bool);
	REGISTER_FACT(IBFactDef_IsOnTable);
	REGISTER_FACT(IBFactDef_IsTopOf);
}

#define REGISTER_ACTION(a) m_oActionLibrary.RegisterActionDef(#a, new a(this))

void IBPlanner::InitActionLibrary()
{
	REGISTER_ACTION(IBActionDef_BoolToBool);
}

void IBPlanner::AddGoal(const string& name)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	m_aGoals.insert(pDef->Instanciate());
}

void IBPlanner::AddGoal(const string& name, void* pUserData)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	m_aGoals.insert(pDef->Instanciate(pUserData));
}

void IBPlanner::AddGoal(const string& name, void* pUserData1, void* pUserData2)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	m_aGoals.insert(pDef->Instanciate(pUserData1, pUserData2));
}

void IBPlanner::AddGoal(const string& name, void* pUserData1, void* pUserData2, void* pUserData3)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	m_aGoals.insert(pDef->Instanciate(pUserData1, pUserData2, pUserData3));
}

int IBPlanner::Step()
{
	for (FactSet::iterator it = m_aGoals.begin() ; it != m_aGoals.end() ; ++it)
	{
		IBFact* pFact = *it;

		IBF_Result res = pFact->Test();

		LOG("Result : %d\n", res);
	}

	return 0;
}