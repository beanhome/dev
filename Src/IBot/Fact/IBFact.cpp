#include "IBFact.h"
#include "Action/IBActionDef.h"
#include "IBPlanner.h"

#include "Utils.h"

IBFact::IBFact(IBFactDef* pDef, const vector<IBObject*>& aUserData)
	: m_pDef(pDef)
	, m_aUserData(aUserData)
	, m_pCauseAction(NULL)
	, m_pEffectAction(NULL)
	, m_bToDelete(false)
{
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
}

void IBFact::SetVariable(uint i, IBObject* pVar)
{
	ASSERT(i<m_aUserData.size());
	m_aUserData[i] = pVar;

	if (m_pCauseAction != NULL)
		m_pCauseAction->ResolvePostCondVariable();
}

void IBFact::PrepareToDelete()
{
	m_bToDelete = true;

	if (m_pCauseAction != NULL)
		m_pCauseAction->PrepareToDelete();
}


bool IBFact::Resolve(IBPlanner* pPlanner)
{
	if (m_pCauseAction != NULL && m_pCauseAction->Resolve(pPlanner) == IBAction::IBA_Destroyed)
	{
		m_pCauseAction->PrepareToDelete();
		if (m_pCauseAction->IsReadyToDelete())
		{
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


