#include "IBPlanner.h"

#include "Fact/IBFact.h"
#include "Fact/Def/IBFactDef_True.h"
#include "Fact/Def/IBFactDef_False.h"
#include "Fact/Def/IBFactDef_Bool.h"
#include "Fact/Def/IBFactDef_IsOnTable.h"
#include "Fact/Def/IBFactDef_IsTopOf.h"
#include "Fact/Def/IBFactDef_IsFree.h"

#include "Action/IBAction.h"
#include "Action/Def/IBActionDef_BoolToBool.h"
#include "Action/Def/IBActionDef_MoveCubeFromTableToCube.h"
#include "Action/Def/IBActionDef_MoveCubeFromCubeToCube.h"
#include "Action/Def/IBActionDef_MoveCubeFromCubeToTable.h"


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

#define REGISTER_FACT(a) m_oFactLibrary.RegisterFactDef(#a, new a(#a))

void IBPlanner::InitFactLibrary()
{
	REGISTER_FACT(IBFactDef_True);
	REGISTER_FACT(IBFactDef_False);
	REGISTER_FACT(IBFactDef_Bool);
	REGISTER_FACT(IBFactDef_IsOnTable);
	REGISTER_FACT(IBFactDef_IsFree);
	REGISTER_FACT(IBFactDef_IsTopOf);
}

#define REGISTER_ACTION(a) m_oActionLibrary.RegisterActionDef(#a, new a(#a, this))

void IBPlanner::InitActionLibrary()
{
	REGISTER_ACTION(IBActionDef_BoolToBool);
	REGISTER_ACTION(IBActionDef_MoveCubeFromTableToCube);
	REGISTER_ACTION(IBActionDef_MoveCubeFromCubeToTable);
	REGISTER_ACTION(IBActionDef_MoveCubeFromCubeToCube);
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

	vector<void*> aUserData;
	aUserData.push_back(pUserData);
	m_aGoals.insert(pDef->Instanciate(aUserData));
}

void IBPlanner::AddGoal(const string& name, void* pUserData1, void* pUserData2)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	vector<void*> aUserData;
	aUserData.push_back(pUserData1);
	aUserData.push_back(pUserData2);
	m_aGoals.insert(pDef->Instanciate(aUserData));
}

void IBPlanner::AddGoal(const string& name, void* pUserData1, void* pUserData2, void* pUserData3)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	vector<void*> aUserData;
	aUserData.push_back(pUserData1);
	aUserData.push_back(pUserData2);
	aUserData.push_back(pUserData3);
	m_aGoals.insert(pDef->Instanciate(aUserData));
}

int IBPlanner::Step()
{
	bool res = false;

	for (FactSet::iterator it = m_aGoals.begin() ; it != m_aGoals.end() ; ++it)
	{
		IBFact* pFact = *it;
		res = pFact->Resolve(this);
	}

	return (int)res;
}

int IBPlanner::FindActionToResolve(IBFact* pFact)
{
	m_oActionLibrary.FindActionDef(pFact);

	return 0;
}

void IBPlanner::Print() const
{
	LOG("\n");
	LOG("Plan : \n");
	for (FactSet::const_iterator it = m_aGoals.begin() ; it != m_aGoals.end() ; ++it)
	{
		IBFact* pFact = *it;

		pFact->Print(0);
	}
	LOG("\n");
}

