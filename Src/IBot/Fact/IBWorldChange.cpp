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
	for (WorldChangeSet::iterator it = m_aDuplicats.begin(); it != m_aDuplicats.end(); ++it)
	{
		IBWorldChange* pDuplicat = *it;
		pDuplicat->RemDuplicat(this);
	}
	m_aDuplicats.clear();

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

int IBWorldChange::GetFactCost() const
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

	return iFactCost;
}

float IBWorldChange::GetActionCost() const
{
	return (m_pAction != nullptr ? m_pAction->GetTotalCost() : 0.f);
}

IBCost IBWorldChange::GetCost() const
{
	return IBCost(GetActionCost(), GetFactCost());
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

			if (pPreWC->GetBestDuplicat() != pPreWC)
				continue;

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

void	 IBWorldChange::AddDuplicat(IBWorldChange* pDuplicat)
{
	ASSERT(pDuplicat != this);
	m_aDuplicats.insert(pDuplicat);
}

void	 IBWorldChange::RemDuplicat(IBWorldChange* pDuplicat)
{
	m_aDuplicats.erase(pDuplicat);
}

bool	 IBWorldChange::IsDuplicat(const IBWorldChange* pDuplicat) const
{
	return m_aDuplicats.find((IBWorldChange*)pDuplicat) != m_aDuplicats.end();
}

void IBWorldChange::UpdateDuplicats()
{
	IBWorldChange* pFirstDuplicat = m_pPlanner->GetGoals().FindFirstDuplicat(this);
	if (pFirstDuplicat == nullptr)
		return;

	for (WorldChangeSet::iterator it = pFirstDuplicat->GetDuplicats().begin(); it != pFirstDuplicat->GetDuplicats().end(); ++it)
	{
		IBWorldChange* pDuplicat = *it;
		AddDuplicat(pDuplicat);
		pDuplicat->AddDuplicat(this);
	}

	pFirstDuplicat->AddDuplicat(this);
	AddDuplicat(pFirstDuplicat);
}

bool IBWorldChange::IsEqual(const IBWorldChange* pOther) const
{
	if (pOther == this)
		return true;

	bool bFound = false;

	for (FactSet::iterator a = GetFacts().begin(); a != GetFacts().end(); ++a)
	{
		IBFact* pA = *a;

		bFound = false;
		for (FactSet::iterator b = pOther->GetFacts().begin(); b != pOther->GetFacts().end(); ++b)
		{
			IBFact* pB = *b;

			if (pA->IsEqual(pB))
			{
				bFound = true;
				break;
			}
		}

		if (!bFound)
			break;
	}

	return bFound;
}

IBWorldChange* IBWorldChange::FindFirstDuplicat(const IBWorldChange* pModel) const
{
	if (pModel != this && IsEqual(pModel))
		return (IBWorldChange*)this;

	for (FactSet::const_iterator it_fact = GetFacts().begin(); it_fact != GetFacts().end(); ++it_fact)
	{
		const IBFact* pFact = *it_fact;

		for (ActionSet::const_iterator it = pFact->GetCauseAction().begin(); it != pFact->GetCauseAction().end(); ++it)
		{
			IBAction* pAction = *it;
			if (pAction == nullptr)
				continue;

			IBWorldChange* pPreChange = pAction->GetPreWorldChange();
			if (pPreChange == nullptr)
				continue;

			if (pPreChange != pModel && pPreChange->IsEqual(pModel))
				return pPreChange;
		}
	}

	for (FactSet::const_iterator it_fact = GetFacts().begin(); it_fact != GetFacts().end(); ++it_fact)
	{
		const IBFact* pFact = *it_fact;

		for (ActionSet::const_iterator it = pFact->GetCauseAction().begin(); it != pFact->GetCauseAction().end(); ++it)
		{
			IBAction* pAction = *it;
			if (pAction == nullptr)
				continue;

			const IBWorldChange* pPreChange = pAction->GetPreWorldChange();
			if (pPreChange == nullptr)
				continue;

			IBWorldChange* pDuplicat = pPreChange->FindFirstDuplicat(pModel);
			if (pDuplicat != nullptr)
				return pDuplicat;
		}
	}

	return nullptr;
}

IBWorldChange* IBWorldChange::GetBestDuplicat()
{
	IBWorldChange* pBestWorldChange = this;

	for (WorldChangeSet::iterator it = m_aDuplicats.begin(); it != m_aDuplicats.end(); ++it)
	{
		IBWorldChange* pDuplicat = *it;

		if (pDuplicat->GetActionCost() < pBestWorldChange->GetActionCost())
		{
			pBestWorldChange = pDuplicat;
		}
	}

	return pBestWorldChange;
}

void IBWorldChange::Step(const IBPlanner* pPlanner)
{
	if (IsTrue())
		return;

	if (GetFacts().size() > 0)
	{
		const ActionDefSet& AllActionDef = pPlanner->GetActionLibrary().GetAllActionDef();

		for (FactSet::iterator it_fact = GetFacts().begin(); it_fact != GetFacts().end(); ++it_fact)
		{
			IBFact* pFact = *it_fact;

			ASSERT(pFact->m_pWorldChangeOwner == this);

			//if (pFact->IsTrue())
			//	continue;

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
