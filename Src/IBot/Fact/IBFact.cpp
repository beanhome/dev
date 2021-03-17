#include "IBFact.h"
#include "Fact/IBFactDef.h"
#include "Action/IBActionDef.h"
#include "IBPlanner.h"

#include "Utils.h"
#include "World/IBObject.h"

IBFact::IBFact(const IBFactDef* pDef, bool bInverted, const vector<IBObject>& aVariables, class IBNode* pNodeOwner, IBPlanner* pPlanner)
	: m_pPlanner(pPlanner)
	, m_pDef(pDef)
	, m_bInverted(bInverted)
	, m_pNodeOwner(pNodeOwner)
{
	ASSERT(aVariables.size() == pDef->GetDegree());

	for (uint i=0 ; i<aVariables.size() ; ++i)
		m_aVariables.insert(VarPair(pDef->GetVariableName(i), aVariables[i]));
}

IBFact::~IBFact()
{
}

IBFact* IBFact::Clone() const
{
	IBFact* pFact = new IBFact(*this);
	return pFact;
}

void IBFact::Destroy()
{
	for (ActionSet::const_iterator it = m_aCauseAction.begin(); it != m_aCauseAction.end(); ++it)
	{
		IBAction* pAction = *it;
		pAction->Destroy();
		delete pAction;
	}
	
	m_aCauseAction.clear();
}

const IBFactDef* IBFact::GetFactDef() const
{
	return m_pDef;
}

bool IBFact::HasCauseAction() const
{
	return (m_aCauseAction.size() > 0);
}

void IBFact::RemoveCauseAction(class IBAction* pAction)
{
	m_aCauseAction.erase(pAction);
}

void IBFact::AddCauseAction(class IBAction* pAction)
{
	if (m_aCauseAction.find(pAction) == m_aCauseAction.end())
		m_aCauseAction.insert(pAction);
}

const ActionSet& IBFact::GetCauseAction() const
{
	return m_aCauseAction;
}

const VarMap& IBFact::GetVariables() const
{
	return m_aVariables;
}

const IBObject* IBFact::GetVariable(const char* varname) const
{
	ASSERT(varname != nullptr || m_pDef->GetDegree() == 1);

	VarMap::const_iterator it = (varname != nullptr ? m_aVariables.find(varname) : m_aVariables.begin());
	ASSERT(it != m_aVariables.end());
	return (it == m_aVariables.end() ? nullptr : &it->second);
}

void IBFact::SetVariable(const string& varname, const IBObject& obj)
{
	VarMap::iterator it = m_aVariables.find(varname);
	ASSERT(it != m_aVariables.end());
	if (it != m_aVariables.end())
		it->second = obj;
}

void IBFact::SetVariable(const IBObject& obj)
{
	ASSERT(m_pDef->GetDegree() == 1);
	ASSERT(m_aVariables.size() == 1);

	m_aVariables.begin()->second = obj;
}


void IBFact::ResolveVariableFromCond(const class IBAction* pAction, const IBFactCondDef& oCondDef)
{
	for (uint i = 0; i < oCondDef.m_aLinkNames.size(); ++i)
	{
		const IBObject* pObj = pAction->GetVariable(oCondDef.m_aLinkNames[i].m_sActionVarName);
		if (pObj)
			SetVariable(oCondDef.m_aLinkNames[i].m_sCondVarName, *pObj);
	}
}

bool IBFact::IsEqual(const IBFact* other) const
{
	ASSERT(other != nullptr);

	if (m_pDef != other->m_pDef)
		return false;

	if (m_bInverted != other->m_bInverted)
		return false;

	return m_pDef->HasSameVariables(this, other);
}

bool IBFact::IsOpposite(const IBFact* other) const
{
	ASSERT(other != nullptr);

	if (m_pDef != other->m_pDef)
		return false;

	if (!m_pDef->HasSameVariables(this, other))
		return false;

	return (m_bInverted != other->m_bInverted);
}

bool IBFact::operator==(const IBFact& other) const
{
	return IsEqual(&other);
}

bool IBFact::operator!=(const IBFact& other) const
{
	return !IsEqual(&other);
}

void IBFact::Resolve(const IBPlanner* pPlanner)
{
	const ActionDefSet& AllActionDef = pPlanner->GetActionLibrary().GetAllActionDef();

	// For each Action in lib
	for (ActionDefSet::const_iterator it = AllActionDef.begin(); it != AllActionDef.end(); ++it)
	{
		IBActionDef* pActionDef = *it;

		if (IsResolvableBy(pActionDef))
		{
			IBAction* pAction = pActionDef->Instanciate(this);
			AddCauseAction(pAction);
		}
	}
}

bool IBFact::IsResolvableBy(const class IBActionDef* pActionDef) const
{
	// Action propose to resolve pFact
	bool found = false;
	for (uint i = 0; i < pActionDef->GetPostCondDef().size(); ++i)
	{
		const IBFactCondDef& oDef = pActionDef->GetPostCondDef()[i];
		if (m_pDef->GetName() == oDef.m_pFactDef->GetName()
			&& m_bInverted == oDef.m_bInverted)
		{
			found = true;
			break;
		}
	}

	return found;
}


void IBFact::Update()
{
	/*
	if (IsTrue())
	{
		IBAction* pCurrentAction = m_pPlanner->GetCurrentAction();
		if (pCurrentAction != nullptr && pCurrentAction->IsChildOf(this))
		{
			pCurrentAction->Stop(true);
			m_pPlanner->SetCurrentAction(nullptr);
		}
		else
		{
			for (ActionSet::iterator it = m_aCauseAction.begin(); it != m_aCauseAction.end(); ++it)
			{
				IBAction* pAction = *it;
				pAction->Destroy();
				delete pAction;
			}

			m_aCauseAction.clear();
		}
	}

	if (IsTrue() == false && m_aCauseAction.size() == 0)
	{

	}
	*/

	for (ActionSet::iterator it = m_aCauseAction.begin(); it != m_aCauseAction.end(); /* blank */)
	{
		IBAction* pAction = *it;

		if (pAction->GetState() == IBA_State::IBA_Destroyed)
		{
			RemoveCauseAction(*it++);
			delete pAction;
		}
		else
		{
			pAction->Update();
			++it;
		}
	}
}

bool IBFact::IsImpossible() const
{
	if (IsTrue())
		return false;

	bool bImpossible = (m_aCauseAction.size() > 0);

	for (ActionSet::iterator it = m_aCauseAction.begin(); it != m_aCauseAction.end(); ++it)
	{
		IBAction* pAction = *it;

		if (pAction->GetState() != IBA_State::IBA_Impossible)
			bImpossible = false;
	}

	return bImpossible;
}

IBF_Result IBFact::Test() const
{
	return m_pDef->Test(this);
}

bool IBFact::IsTrue() const
{
	return (Test() == IBF_Result::IBF_OK) != m_bInverted;
}

int IBFact::GetCost() const
{
	if (IsImpossible())
		return INT32_MAX;

	return (IsTrue() ? 0 : 1);
}
