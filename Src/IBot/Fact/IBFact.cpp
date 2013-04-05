#include "IBFact.h"
#include "Action/IBActionDef.h"
#include "IBPlanner.h"

#include "Utils.h"
#include "World/IBObject.h"

IBFact::IBFact(IBFactDef* pDef, const vector<IBObject*>& aUserData)
	: m_pDef(pDef)
	, m_aUserData(aUserData)
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
	while (m_aCauseAction.begin() != m_aCauseAction.end())
	{
		delete *(m_aCauseAction.begin());
	}

#if 0
	for (ActionSet::iterator it = m_aCauseAction.begin() ; it != m_aCauseAction.end() ; /*++it*/)
	{
		IBAction* pAction = *it;

		//if (pAction->GetPostCond().size() == 1)
		{
			delete pAction;
			it++;
		}
		/*
		else
		{
			pAction->RemPostCond(this);
			it++;
		}
		*/
	}
#endif

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
	if (pVar != NULL && pVar->IsInstance() && pVar->GetOwner() == NULL)
		pVar->SetOwner(this);

	for (ActionSet::iterator it = m_aCauseAction.begin() ; it != m_aCauseAction.end() ; ++it)
		(*it)->UpdateVariableFromPostCond();
}

bool IBFact::IsReadyToDelete() const
{
	if (!m_bToDelete)
		return false;

	for (ActionSet::const_iterator it = m_aCauseAction.begin() ; it != m_aCauseAction.end() ; ++it)
	{
		if (!(*it)->IsReadyToDelete())
			return false;
	}

	return true;
}


void IBFact::PrepareToDelete()
{
	m_bToDelete = true;

	for (ActionSet::iterator it = m_aCauseAction.begin() ; it != m_aCauseAction.end() ; ++it)
		(*it)->PrepareToDelete();
}

IBAction* IBFact::GetBestCauseAction(float& fMinEval) const
{
	IBAction* pBestAction = NULL;
	fMinEval = IBPlanner::s_fMaxActionDelay;
	for (ActionSet::const_iterator it = m_aCauseAction.begin() ; it != m_aCauseAction.end() ; ++it)
	{
		IBAction* pAction = *it;

		float fEval = pAction->Evaluate();
		if (pBestAction == NULL || fMinEval > fEval)
		{
			pBestAction = pAction;
			fMinEval = fEval;
		}
	}

	return pBestAction;
}


float IBFact::Evaluate() const
{
	if (Test() == IBF_OK)
		return 0.f;

	float fEval;
	GetBestCauseAction(fEval);

	return fEval;
}

IBF_Result IBFact::Resolve(IBPlanner* pPlanner, bool bExecute)
{
	for (ActionSet::iterator it = m_aCauseAction.begin(); it != m_aCauseAction.end(); /* blank */)
	{
		if ((*it)->IsReadyToDelete())
		{
			delete *it++; // the delete do the erase
			//m_aCauseAction.erase(it++);
		}
		else
		{
			++it;
		}
	}

	//if (m_pEffectAction != NULL && m_pEffectAction->GetState() == IBAction::IBA_Impossible)
	//	return IBF_IMPOSSIBLE;

	IBF_Result res = Test();

	multimap<float, IBAction*> pActionOrdered;

	for (ActionSet::iterator it = m_aCauseAction.begin() ; it != m_aCauseAction.end() ; ++it)
		pActionOrdered.insert(pair<float, IBAction*>((*it)->Evaluate(), (*it)));

	switch (res)
	{
		case IBF_OK:
			for (multimap<float, IBAction*>::iterator it = pActionOrdered.begin() ; it != pActionOrdered.end() ; ++it)
			{
				IBAction* pAction = it->second;
				pAction->PrepareToDelete();
				pAction->Resolve(pPlanner, bExecute);
			}
			break;

		case IBF_FAIL:
			if (!m_bToDelete && m_aCauseAction.size() == 0)
			{
				pPlanner->FindActionToResolve(this);
				if (m_aCauseAction.size() == 0)
					res = IBF_IMPOSSIBLE;
			}
			else
			{
				bool imp = true;
				for (multimap<float, IBAction*>::iterator it = pActionOrdered.begin() ; it != pActionOrdered.end() ; ++it)
				{
					IBAction* pAction = it->second;

					if (m_bToDelete)
						pAction->PrepareToDelete();

					IBAction::State st = pAction->Resolve(pPlanner, bExecute);

					if (st != IBAction::IBA_Impossible)
						imp = false;

					if (!m_bToDelete && st == IBAction::IBA_Destroyed)
						pAction->PrepareToDelete();
				}
				if (imp)
					res = IBF_IMPOSSIBLE;
			}
			break;

		case IBF_UNKNOW:
			// Find variable object
			ResolveVariable();
			if (GetEffectAction() != NULL)
				GetEffectAction()->SpreadPreCondVariable(this);
			break;
	}

	return (m_bToDelete ? IBF_DELETE : res);
}


