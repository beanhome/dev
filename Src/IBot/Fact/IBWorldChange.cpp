#include "IBWorldChange.h"
#include "Action/IBActionDef.h"
#include "IBPlanner.h"

#include "Utils.h"
#include "World/IBObject.h"

IBWorldChange::IBWorldChange(class IBPlanner* pPlanner, IBAction* pEffectAction)
	: m_pPlanner(pPlanner)
	, m_pAction(pEffectAction)
{
}


IBWorldChange::IBWorldChange(class IBPlanner* pPlanner, const vector<class IBFact*>& WorldChange)
	: m_pPlanner(pPlanner)
	, m_pAction(nullptr)
{
	for (uint i = 0; i < WorldChange.size(); ++i)
		m_aFacts.insert(WorldChange[i]->Clone());
}

IBWorldChange::~IBWorldChange()
{
	ASSERT(m_aFacts.size() == 0);
}

void IBWorldChange::Destroy()
{
	for (FactSet::iterator it = m_aFacts.begin() ; it != m_aFacts.end(); ++it)
	{
		IBFact* pFact = *it;
		pFact->Destroy();
		delete pFact;
	}
	m_aFacts.clear();
}

bool IBWorldChange::operator==(const IBWorldChange& other) const
{
	ASSERT(false); // TODO

	return false;
}

const FactSet& IBWorldChange::GetFacts() const
{
	return m_aFacts;
}

uint	 IBWorldChange::Size() const
{
	return m_aFacts.size();
}

void IBWorldChange::AddFact(class IBFact* pFact)
{
	m_aFacts.insert(pFact);

	if (pFact->m_pWorldChangeOwner == nullptr)
		pFact->m_pWorldChangeOwner = this;

	ASSERT(pFact->m_pWorldChangeOwner == this);
}

void IBWorldChange::RemFact(class IBFact* pFact)
{
	m_aFacts.erase(pFact);
}

/*
const IBFact* IBWorldChange::FindFact(const string& name) const
{
	for (FactSet::iterator it = m_aFacts.begin(); it != m_aFacts.end(); ++it)
	{
		IBFact* pFact = *it;
		if (pFact != nullptr && pFact->GetFactDef()->GetName() == name)
			return pFact;
	}

	return nullptr;
}
*/

bool IBWorldChange::IsTrue() const
{
	for (FactSet::iterator it = m_aFacts.begin(); it != m_aFacts.end(); ++it)
	{
		IBFact* pFact = *it;
		if (pFact == nullptr || pFact->IsTrue() == false)
			return false;
	}

	return true;
}


IBCost IBWorldChange::GetCost() const
{
	int iFactCost = 0;

	for (FactSet::iterator it = m_aFacts.begin(); it != m_aFacts.end(); ++it)
	{
		IBFact* pFact = *it;
		int iCost = pFact->GetCost();
		if (iCost == INT32_MAX)
		{
			iFactCost = INT32_MAX;
			break;
		}
		iFactCost += iCost;
	}

	float fActionCost = (m_pAction != nullptr ? m_pAction->GetTotalCost() : 0.f);

	return IBCost(fActionCost, iFactCost);
}

void	 IBWorldChange::Update()
{
	for (FactSet::iterator it_fact = GetFacts().begin(); it_fact != GetFacts().end(); ++it_fact)
	{
		IBFact* pFact = *it_fact;

		pFact->Update();
	}
}

IBWorldChange* IBWorldChange::GetBestWorldChange() const
{
	IBCost oBestCost = IBCost::MaxCost;
	IBWorldChange* pBestWorldChange = (IBWorldChange*)this;

	for (FactSet::iterator it_fact = GetFacts().begin(); it_fact != GetFacts().end(); ++it_fact)
	{
		IBFact* pFact = *it_fact;

		for (ActionSet::const_iterator it = pFact->GetCauseAction().begin(); it != pFact->GetCauseAction().end(); ++it)
		{
			IBAction* pAction = *it;

			if (pAction->GetState() == IBA_State::IBA_Impossible)
				continue;

			IBWorldChange* pPreWC = pAction->GetPreWorldChange();
			if (pPreWC == nullptr)
				continue;

			pPreWC = pPreWC->GetBestWorldChange();

			IBCost oPreWCCost = pPreWC->GetCost();

			if (oPreWCCost < oBestCost)
			{
				pBestWorldChange = pPreWC;
				oBestCost = oPreWCCost;
			}
		}
	}

	//return (oBestCost < GetCost() ? pBestWorldChange : (IBWorldChange*)this);
	return pBestWorldChange;
}

bool IBWorldChange::CheckCompatibility(const IBFact* pCond) const
{
	for (FactSet::iterator it = GetFacts().begin(); it != GetFacts().end(); ++it)
	{
		IBFact* pFact = *it;
		if (pFact->IsOpposite(pCond))
			return false;
	}

	if (m_pAction == nullptr)
		return true;

	ASSERT(m_pAction->m_pPostWorldChange != nullptr);

	return m_pAction->m_pPostWorldChange->CheckCompatibility(pCond);
}

bool IBWorldChange::CheckInnerCompatibility() const
{
	for (FactSet::iterator a = GetFacts().begin(); a != GetFacts().end(); ++a)
	{
		IBFact* pA = *a;

		for (FactSet::iterator b = a; b != GetFacts().end(); ++b)
		{
			IBFact* pB = *b;

			if (pA == pB)
				continue;

			if (pA->IsOpposite(pB))
				return false;

			if (!m_pPlanner->AreCompatible(pA, pB))
				return false;

			if (pA->GetFactDef() != pB->GetFactDef() && !m_pPlanner->AreCompatible(pB, pA))
				return false;
		}
	}

	return true;
}


void IBWorldChange::Step(const IBPlanner* pPlanner)
{
	if (GetFacts().size() > 0)
	{
		const ActionDefSet& AllActionDef = pPlanner->GetActionLibrary().GetAllActionDef();

		for (FactSet::iterator it_fact = GetFacts().begin(); it_fact != GetFacts().end(); ++it_fact)
		{
			IBFact* pFact = *it_fact;

			ASSERT(pFact->m_pWorldChangeOwner == this);

			if (pFact->IsTrue())
				continue;

			if (pFact->GetCauseAction().size() > 0)
				continue;

			pFact->Resolve(pPlanner);
		}
	}
}

bool IBWorldChange::FactIsResolvableBy(const class IBFact* pFact, const class IBActionDef* pActionDef) const
{
	// pFact come from this
	ASSERT(m_aFacts.find((IBFact*)pFact) != m_aFacts.end());

	// Action propose to resolve pFact
	bool found = false;
	for (uint i = 0; i < pActionDef->GetPostCondDef().size(); ++i)
	{
		const IBFactCondDef& oDef = pActionDef->GetPostCondDef()[i];
		if (pFact->GetFactDef()->GetName() == oDef.m_pFactDef->GetName()
		 && pFact->IsInverted() == oDef.m_bInverted)
		{
			found = true;
			break;
		}
	}

	if (!found)
		return false;

	return true;
}
