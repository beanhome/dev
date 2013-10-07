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
}

void IBFact::Destroy()
{
	while (m_aCauseAction.begin() != m_aCauseAction.end())
	{
		IBAction* pAction = *m_aCauseAction.begin();
		pAction->Destroy();
		delete pAction;
	}

	for (uint i=0 ; i<m_aUserData.size() ; ++i)
	{
		if (m_aUserData[i] != NULL && m_aUserData[i]->IsInstance() && m_aUserData[i]->GetOwner() == this)
		{
			delete m_aUserData[i];
		}
	}
}

bool IBFact::operator==(const IBFact& other) const
{
	if (m_pDef != other.m_pDef)
		return false;

	ASSERT(m_aUserData.size() == other.m_aUserData.size());			

	for (uint i=0 ; i<m_aUserData.size() ; ++i)
	{
		if (m_aUserData[i] != other.m_aUserData[i])
			return false;
	}

	return true;
}

SortedActionSet IBFact::GetActionOrdered() const
{
	SortedActionSet pActionOrdered;

	for (ActionSet::iterator it = m_aCauseAction.begin() ; it != m_aCauseAction.end() ; ++it)
		pActionOrdered.insert(*it);

	return pActionOrdered;
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

bool IBFact::IsReadyToDestroy() const
{
	if (!m_bToDelete)
		return false;

	for (ActionSet::const_iterator it = m_aCauseAction.begin() ; it != m_aCauseAction.end() ; ++it)
	{
		if (!(*it)->IsReadyToDestroy())
			return false;
	}

	return true;
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
	fMinEval = 0.f;
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

	SortedActionSet pActionOrdered = GetActionOrdered();

	bool bResolved = false;

	switch (res)
	{
		case IBF_OK:
			for (SortedActionSet::iterator it = pActionOrdered.begin() ; it != pActionOrdered.end() ; ++it)
			{
				IBAction* pAction = *it;
				pAction->PrepareToDelete();
				pAction->Resolve(pPlanner, bExecute);
			}
			break;

		case IBF_FAIL:
			// TODO Find Equal Fact BottomTop
			// -> Impossible
			if (FindEqualFact_BottomTop(this) != NULL)
			{
				res = IBF_IMPOSSIBLE;
			}
			else if (!m_bToDelete && m_aCauseAction.size() == 0)
			{
				pPlanner->FindActionToResolve(this);
				if (m_aCauseAction.size() == 0)
					res = IBF_IMPOSSIBLE;
			}
			else
			{
				bool imp = true;
				bool resolved = false;
				for (SortedActionSet::iterator it = pActionOrdered.begin() ; it != pActionOrdered.end() ; ++it)
				{
					IBAction* pAction = *it;

					if (m_bToDelete)
						pAction->PrepareToDelete();

					if (bResolved)
						pAction->PrepareToDelete();

					IBAction::State st = pAction->Resolve(pPlanner, bExecute);
					bResolved = pAction->IsResolved();

					if (st != IBAction::IBA_Destroyed)
						bExecute = false;

					if (st != IBAction::IBA_Impossible)
						imp = false;

					if (!m_bToDelete && st == IBAction::IBA_Destroyed)
						pAction->PrepareToDelete();
				}

				if (imp)
					res = IBF_IMPOSSIBLE;
				else if (bResolved)
					res = IBF_RESOLVED;
			}
			break;

		case IBF_UNKNOW:
			// Find variable object
			ResolveVariable();
			if (GetEffectAction() != NULL)
				GetEffectAction()->SpreadPreCondVariable(this);
			break;
	}

	res = (m_bToDelete ? IBF_DELETE : res);

	return res;
}

bool IBFact::IsResolved() const
{
	if (IsTrue())
		return true;

	for (ActionSet::const_iterator it = m_aCauseAction.begin() ; it != m_aCauseAction.end() ; ++it)
	{
		IBAction* pAction = *it;

		if (pAction->IsResolved())
			return true;
	}

	return false;
}

const IBFact* IBFact::FindEqualFact_BottomTop(IBFact* pModelFact) const
{
	if (this != pModelFact && *this == *pModelFact)
		return this;

	return (m_pEffectAction != NULL ? m_pEffectAction->FindEqualFact_BottomTop(pModelFact) : NULL);
}

