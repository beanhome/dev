#include "IBPlanner.h"

#include "Fact/IBFact.h"
#include "Fact/Def/IBFactDef_True.h"
#include "Fact/Def/IBFactDef_False.h"
#include "Fact/Def/IBFactDef_Bool.h"

#include "Action/IBAction.h"
#include "Action/Def/IBActionDef_BoolToBool.h"

float IBPlanner::s_fMaxActionDelay = 10.f;


IBPlanner::IBPlanner(void* pOwner)
	: m_pOwner(pOwner)
	, m_oGoals(this)
	, m_pCurrentAction(nullptr)
	, m_pBestNode(nullptr)
	, m_iStepCount(0)
{
	REGISTER_FACT(IBFactDef_True);
	REGISTER_FACT(IBFactDef_False);
	REGISTER_FACT(IBFactDef_Bool);

	REGISTER_ACTION(IBActionDef_BoolToBool);
}

IBPlanner::~IBPlanner()
{
	m_oGoals.Destroy();
}

IBAction* IBPlanner::InstanciateAction(const string& sActionName, IBFact* pPostCond)
{
	IBActionDef* pActionDef = m_oActionLibrary.FindActionDef(sActionName);
	return (pActionDef != nullptr ? InstanciateAction(pActionDef, pPostCond) : nullptr);
}

IBAction* IBPlanner::InstanciateAction(const IBActionDef* pDef, IBFact* pPostCond)
{
	return new IBAction(pDef, pPostCond, this);
}

IBFact* IBPlanner::InstanciateFact(const string& sFactName, bool bInverted, const vector<IBObject>& aVariables, IBWorldChange* pWorldChange)
{
	IBFactDef* pFactDef = m_oFactLibrary.GetFactDef(sFactName);
	return (pFactDef != nullptr ? InstanciateFact(pFactDef, bInverted, aVariables, pWorldChange) : nullptr);
}

IBFact* IBPlanner::InstanciateFact(const IBFactDef* pDef, bool bInverted, const vector<IBObject>& aVariables, IBWorldChange* pWorldChange)
{
	return new IBFact(pDef, bInverted, aVariables, pWorldChange, this);
}

void IBPlanner::AddGoal(const string& name, bool bTrue)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != nullptr);

	m_oGoals.AddFact(pDef->Instanciate(!bTrue));
}

void IBPlanner::AddGoal(const string& name, bool bTrue, const vector<IBObject>& aObjects)
{
	IBFactDef* pDef = GetFactDef(name);
	assert(pDef != nullptr);

	m_oGoals.AddFact(pDef->Instanciate(!bTrue, &m_oGoals, aObjects));
}

void IBPlanner::AddGoal(const string& fact_name, bool bTrue, const string& var_name, void* pUserData)
{
	IBFactDef* pDef = GetFactDef(fact_name);
	assert(pDef != nullptr);

	vector<IBObject> aVariables;
	aVariables.push_back(IBObject(var_name, pUserData));
	m_oGoals.AddFact(pDef->Instanciate(!bTrue, &m_oGoals, aVariables));
}

void IBPlanner::AddGoal(const string& fact_name, bool bTrue, const string& sVarName1, void* pUserData1, const string& sVarName2, void* pUserData2)
{
	IBFactDef* pDef = GetFactDef(fact_name);
	assert(pDef != nullptr);

	vector<IBObject> aVariables;
	aVariables.push_back(IBObject(sVarName1, pUserData1));
	aVariables.push_back(IBObject(sVarName2, pUserData2));
	m_oGoals.AddFact(pDef->Instanciate(!bTrue, &m_oGoals, aVariables));
}

void IBPlanner::AddGoal(const string& fact_name, bool bTrue, const string& sVarName1, void* pUserData1, const string& sVarName2, void* pUserData2, const string& sVarName3, void* pUserData3)
{
	IBFactDef* pDef = GetFactDef(fact_name);
	assert(pDef != nullptr);

	vector<IBObject> aVariables;
	aVariables.push_back(IBObject(sVarName1, pUserData1));
	aVariables.push_back(IBObject(sVarName2, pUserData2));
	aVariables.push_back(IBObject(sVarName3, pUserData3));
	m_oGoals.AddFact(pDef->Instanciate(!bTrue, &m_oGoals, aVariables));
}

void IBPlanner::AddGoal(IBFact* goal)
{
	m_oGoals.AddFact(goal);
}

void IBPlanner::RemGoal(IBFact* goal)
{
	m_oGoals.RemFact(goal);
	delete goal;
}

int IBPlanner::Step(bool bExecute, bool bCleanGoal)
{
	if (bCleanGoal)
		CleanGoal();

	m_oGoals.Update();
	m_pBestNode = m_oGoals.GetBestWorldChange();
	m_pBestNode->Step(this);
	m_pBestNode = m_oGoals.GetBestWorldChange();

	// no current action -> take best node action
	if (m_pCurrentAction == nullptr && m_pBestNode != nullptr && m_pBestNode->IsTrue())
	{
		m_pCurrentAction = m_pBestNode->GetAction();
		if (m_pCurrentAction != nullptr)
			m_pCurrentAction->Start();
	}

	// current action pre condition all false
	else if (m_pCurrentAction != nullptr && m_pCurrentAction->GetPreWorldChange()->IsTrue() == false)
	{
		m_pCurrentAction->Stop(true);
		m_pCurrentAction = nullptr;
	}

	// best node action is not current action -> Cancel
	else if (m_pCurrentAction != nullptr && m_pBestNode != nullptr && m_pBestNode->GetAction() != nullptr && m_pCurrentAction != m_pBestNode->GetAction())
	{
		m_pCurrentAction->Stop(true);
		m_pCurrentAction = nullptr;
	}

	// best node action is current action -> update
	else if (m_pCurrentAction != nullptr)
	{
		if (m_pCurrentAction->Execute())
		{
			m_pCurrentAction->Stop(false);
			m_pCurrentAction = nullptr;
		}
	}

	m_iStepCount++;

	return 0;
}

void IBPlanner::CleanGoal()
{
	for (FactSet::iterator it = m_oGoals.GetFacts().begin(); it != m_oGoals.GetFacts().end(); /* blank */)
	{
		IBFact* pFact = *it;
		if (pFact->IsTrue() && pFact->GetCauseAction().size() == 0)
		{
			m_oGoals.RemFact(*it++);
			pFact->Destroy();
			delete pFact;
		}
		else
		{
			++it;
		}
	}
}
