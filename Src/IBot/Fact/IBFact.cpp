#include "IBFact.h"
#include "Action/IBActionDef.h"
#include "IBPlanner.h"

#include "Utils.h"
#include "World/IBObject.h"

IBFact::IBFact(IBFactDef* pDef, const vector<IBObject*>& aUserData)
	: m_pDef(pDef)
	, m_aUserData(aUserData)
	, m_pCauseAction(NULL)
	, m_pEffectAction(NULL)
	, m_bToDelete(false)
{
	for (uint i=0 ; i<m_aUserData.size() ; ++i)
	{
		if (m_aUserData[i] != NULL && m_aUserData[i]->IsInstance() && m_aUserData[i]->GetOwner() == NULL)
			m_aUserData[i]->SetOwner(this);
	}
}

IBFact::~IBFact()
{
	if (m_pCauseAction != NULL)
	{
		if (m_pCauseAction->GetPostCond().size() == 1)
		{
			delete m_pCauseAction;
		}
		else
		{
			m_pCauseAction->RemPostCond(this);
		}
	}

	for (uint i=0 ; i<m_aUserData.size() ; ++i)
	{
		if (m_aUserData[i] != NULL && m_aUserData[i]->IsInstance() && m_aUserData[i]->GetOwner() == this)
			delete m_aUserData[i];
	}
}

void IBFact::SetVariable(uint i, IBObject* pVar)
{
	ASSERT(i<m_aUserData.size());
	m_aUserData[i] = pVar;
	if (pVar->IsInstance() && pVar->GetOwner() == NULL)
		pVar->SetOwner(this);

	if (m_pCauseAction != NULL)
		m_pCauseAction->SpreadPostCondVariable();
}

void IBFact::PrepareToDelete()
{
	m_bToDelete = true;

	if (m_pCauseAction != NULL)
		m_pCauseAction->PrepareToDelete();
}

float IBFact::Evaluate() const
{
	if (Test() == IBF_OK)
		return 0.f;

	// TODO: return the smallest cause action value
	return (m_pCauseAction != NULL ? m_pCauseAction->Evaluate() : IBPlanner::s_fMaxActionDelay);
}


bool IBFact::Resolve(IBPlanner* pPlanner)
{
	if (m_pCauseAction != NULL && m_pCauseAction->Resolve(pPlanner) == IBAction::IBA_Destroyed)
	{
		m_pCauseAction->PrepareToDelete();
		if (m_pCauseAction->IsReadyToDelete())
		{
			if (pPlanner->GetCurrentAction() == m_pCauseAction)
				pPlanner->SetCurrentAction(NULL);

			delete m_pCauseAction;
			m_pCauseAction = NULL;
		}
	}

	if (m_bToDelete)
		return false;

	IBF_Result res = Test();
	//LOG("Result : %d\n", res);

	switch (res)
	{
		case IBF_OK:
			if (m_pCauseAction != NULL)
			{
				m_pCauseAction->PrepareToDelete();
			}
			return true;
			break;

		case IBF_FAIL:
			if (m_pCauseAction == NULL)
			{
				pPlanner->FindActionToResolve(this);
			}
			break;

		case IBF_UNKNOW:
			// Find variable object
			// ...
			if (false) { LOG("prout"); }
			break;
	}

	return false;
}


