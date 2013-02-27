#include "IBPlanner.h"

#include "Fact/IBFact.h"
#include "Fact/Def/IBFactDef_True.h"
#include "Fact/Def/IBFactDef_False.h"
#include "Fact/Def/IBFactDef_Bool.h"

#include "Action/IBAction.h"
#include "Action/Def/IBActionDef_BoolToBool.h"
#include "IBGoal.h"


IBPlanner::IBPlanner(void* pOwner)
	: m_pOwner(pOwner)
{
	REGISTER_FACT(IBFactDef_True);
	REGISTER_FACT(IBFactDef_False);
	REGISTER_FACT(IBFactDef_Bool);

	REGISTER_ACTION(IBActionDef_BoolToBool);
}

IBPlanner::~IBPlanner()
{
	for (FactSet::iterator it = m_aGoals.begin() ; it != m_aGoals.end() ; ++it)
		delete (*it);
}


void IBPlanner::InitFactLibrary()
{
}

void IBPlanner::InitActionLibrary()
{
}

IBAction* IBPlanner::InstanciateAction(IBActionDef* pDef)
{
	return new IBAction(pDef);
}

IBFact* IBPlanner::InstanciateFact(IBFactDef* pDef, const vector<IBObject*>& aUserData)
{
	return new IBFact(pDef, aUserData);
}



void IBPlanner::AddGoal(const IBGoal& goal)
{
	IBFactDef* pDef = GetFactDef(goal.GetName());
	assert(pDef != NULL);

	m_aGoals.insert(pDef->Instanciate(goal.GetUserData()));
}


void IBPlanner::AddGoal(const string& name)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	m_aGoals.insert(pDef->Instanciate());
}

void IBPlanner::AddGoal(const string& name, IBObject* pUserData)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	vector<IBObject*> aUserData;
	aUserData.push_back(pUserData);
	m_aGoals.insert(pDef->Instanciate(aUserData));
}

void IBPlanner::AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	vector<IBObject*> aUserData;
	aUserData.push_back(pUserData1);
	aUserData.push_back(pUserData2);
	m_aGoals.insert(pDef->Instanciate(aUserData));
}

void IBPlanner::AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	vector<IBObject*> aUserData;
	aUserData.push_back(pUserData1);
	aUserData.push_back(pUserData2);
	aUserData.push_back(pUserData3);
	m_aGoals.insert(pDef->Instanciate(aUserData));
}

void IBPlanner::AddPreCond(IBAction* pAction, const string& name)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	pAction->AddPreCond(pDef->Instanciate());
}

void IBPlanner::AddPreCond(IBAction* pAction, const string& name, IBObject* pUserData)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	vector<IBObject*> aUserData;
	aUserData.push_back(pUserData);
	pAction->AddPreCond(pDef->Instanciate(aUserData));
}

void IBPlanner::AddPreCond(IBAction* pAction, const string& name, IBObject* pUserData1, IBObject* pUserData2)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	vector<IBObject*> aUserData;
	aUserData.push_back(pUserData1);
	aUserData.push_back(pUserData2);
	pAction->AddPreCond(pDef->Instanciate(aUserData));
}

void IBPlanner::AddPreCond(IBAction* pAction, const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != NULL);

	vector<IBObject*> aUserData;
	aUserData.push_back(pUserData1);
	aUserData.push_back(pUserData2);
	aUserData.push_back(pUserData3);
	pAction->AddPreCond(pDef->Instanciate(aUserData));
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


