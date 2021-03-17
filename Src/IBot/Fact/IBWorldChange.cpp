#include "IBNode.h"
#include "Action/IBActionDef.h"
#include "IBPlanner.h"

#include "Utils.h"
#include "World/IBObject.h"

IBNode::IBNode(class IBPlanner* pPlanner, IBAction* pEffectAction)
	: m_pPlanner(pPlanner)
	, m_pAction(pEffectAction)
{
}


IBNode::IBNode(class IBPlanner* pPlanner, const vector<class IBFact*>& Node)
	: m_pPlanner(pPlanner)
	, m_pAction(nullptr)
{
	for (uint i = 0; i < Node.size(); ++i)
		m_aFacts.insert(Node[i]->Clone());
}

IBNode::~IBNode()
{
	ASSERT(m_aFacts.size() == 0);
}

void IBNode::Destroy()
{
	for (NodeSet::iterator it = m_aDuplicats.begin(); it != m_aDuplicats.end(); ++it)
	{
		IBNode* pDuplicat = *it;
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

bool IBNode::operator==(const IBNode& other) const
{
	ASSERT(false); // TODO

	return false;
}

const FactSet& IBNode::GetFacts() const
{
	return m_aFacts;
}

uint	 IBNode::Size() const
{
	return m_aFacts.size();
}

void IBNode::AddFact(class IBFact* pFact)
{
	m_aFacts.insert(pFact);

	if (pFact->m_pNodeOwner == nullptr)
		pFact->m_pNodeOwner = this;

	ASSERT(pFact->m_pNodeOwner == this);
}

void IBNode::RemFact(class IBFact* pFact)
{
	m_aFacts.erase(pFact);
}

bool IBNode::IsTrue() const
{
	for (FactSet::iterator it = m_aFacts.begin(); it != m_aFacts.end(); ++it)
	{
		IBFact* pFact = *it;
		if (pFact == nullptr || pFact->IsTrue() == false)
			return false;
	}

	return true;
}

int IBNode::GetFactCost() const
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

float IBNode::GetActionCost() const
{
	return (m_pAction != nullptr ? m_pAction->GetTotalCost() : 0.f);
}

IBCost IBNode::GetCost() const
{
	return IBCost(GetActionCost(), GetFactCost());
}

void	 IBNode::Update()
{
	for (FactSet::iterator it_fact = GetFacts().begin(); it_fact != GetFacts().end(); ++it_fact)
	{
		IBFact* pFact = *it_fact;

		pFact->Update();
	}
}

IBNode* IBNode::GetBestNode() const
{
	IBCost oBestCost = IBCost::MaxCost;
	IBNode* pBestNode = (IBNode*)this;

	for (FactSet::iterator it_fact = GetFacts().begin(); it_fact != GetFacts().end(); ++it_fact)
	{
		IBFact* pFact = *it_fact;

		for (ActionSet::const_iterator it = pFact->GetCauseAction().begin(); it != pFact->GetCauseAction().end(); ++it)
		{
			IBAction* pAction = *it;

			if (pAction->GetState() == IBA_State::IBA_Impossible)
				continue;

			IBNode* pPreWC = pAction->GetPreNode();
			if (pPreWC == nullptr)
				continue;

			pPreWC = pPreWC->GetBestNode();

			if (pPreWC->GetBestDuplicat() != pPreWC)
				continue;

			IBCost oPreWCCost = pPreWC->GetCost();

			if (oPreWCCost < oBestCost)
			{
				pBestNode = pPreWC;
				oBestCost = oPreWCCost;
			}
		}
	}

	//return (oBestCost < GetCost() ? pBestNode : (IBNode*)this);
	return pBestNode;
}

bool IBNode::CheckCompatibility(const IBFact* pCond) const
{
	for (FactSet::iterator it = GetFacts().begin(); it != GetFacts().end(); ++it)
	{
		IBFact* pFact = *it;
		if (pFact->IsOpposite(pCond))
			return false;
	}

	if (m_pAction == nullptr)
		return true;

	ASSERT(m_pAction->m_pPostNode != nullptr);

	return m_pAction->m_pPostNode->CheckCompatibility(pCond);
}

bool IBNode::CheckInnerCompatibility() const
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

void	 IBNode::AddDuplicat(IBNode* pDuplicat)
{
	ASSERT(pDuplicat != this);
	m_aDuplicats.insert(pDuplicat);
}

void	 IBNode::RemDuplicat(IBNode* pDuplicat)
{
	m_aDuplicats.erase(pDuplicat);
}

bool	 IBNode::IsDuplicat(const IBNode* pDuplicat) const
{
	return m_aDuplicats.find((IBNode*)pDuplicat) != m_aDuplicats.end();
}

void IBNode::UpdateDuplicats()
{
	IBNode* pFirstDuplicat = m_pPlanner->GetGoals().FindFirstDuplicat(this);
	if (pFirstDuplicat == nullptr)
		return;

	for (NodeSet::iterator it = pFirstDuplicat->GetDuplicats().begin(); it != pFirstDuplicat->GetDuplicats().end(); ++it)
	{
		IBNode* pDuplicat = *it;
		AddDuplicat(pDuplicat);
		pDuplicat->AddDuplicat(this);
	}

	pFirstDuplicat->AddDuplicat(this);
	AddDuplicat(pFirstDuplicat);
}

bool IBNode::IsEqual(const IBNode* pOther) const
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

IBNode* IBNode::FindFirstDuplicat(const IBNode* pModel) const
{
	if (pModel != this && IsEqual(pModel))
		return (IBNode*)this;

	for (FactSet::const_iterator it_fact = GetFacts().begin(); it_fact != GetFacts().end(); ++it_fact)
	{
		const IBFact* pFact = *it_fact;

		for (ActionSet::const_iterator it = pFact->GetCauseAction().begin(); it != pFact->GetCauseAction().end(); ++it)
		{
			IBAction* pAction = *it;
			if (pAction == nullptr)
				continue;

			IBNode* pPreChange = pAction->GetPreNode();
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

			const IBNode* pPreChange = pAction->GetPreNode();
			if (pPreChange == nullptr)
				continue;

			IBNode* pDuplicat = pPreChange->FindFirstDuplicat(pModel);
			if (pDuplicat != nullptr)
				return pDuplicat;
		}
	}

	return nullptr;
}

IBNode* IBNode::GetBestDuplicat()
{
	IBNode* pBestNode = this;

	for (NodeSet::iterator it = m_aDuplicats.begin(); it != m_aDuplicats.end(); ++it)
	{
		IBNode* pDuplicat = *it;

		if (pDuplicat->GetActionCost() < pBestNode->GetActionCost())
		{
			pBestNode = pDuplicat;
		}
	}

	return pBestNode;
}

void IBNode::Step(const IBPlanner* pPlanner)
{
	if (IsTrue())
		return;

	//if (GetFacts().size() > 0)
	{
		//const ActionDefSet& AllActionDef = pPlanner->GetActionLibrary().GetAllActionDef();

		for (FactSet::iterator it_fact = GetFacts().begin(); it_fact != GetFacts().end(); ++it_fact)
		{
			IBFact* pFact = *it_fact;

			ASSERT(pFact->m_pNodeOwner == this);

			//if (pFact->IsTrue())
			//	continue;

			if (pFact->GetCauseAction().size() > 0)
				continue;

			pFact->Resolve(pPlanner);
		}
	}
}

/*
bool IBNode::FactIsResolvableBy(const class IBFact* pFact, const class IBActionDef* pActionDef) const
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
*/
