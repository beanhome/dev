#include "IBAction.h"
#include "World/IBObject.h"
#include "IBActionDef.h"
#include "IBPlanner.h"


IBAction::IBAction(const IBActionDef* pDef, IBFact* pPostCond, IBPlanner* pPlanner)
	: m_pDef(pDef)
	, m_pPlanner(pPlanner)
	, m_eState(IBA_Created)
	, m_pPostNode(nullptr)
	, m_pPreNode(nullptr)
	, m_pUserData(nullptr)
{
	// Set Post Node
	m_pPostNode = pPostCond->m_pNodeOwner;
	m_aPostCond.push_back(pPostCond);

	pPostCond->AddCauseAction(this);
}

void IBAction::Create()
{
	// create action variable
	for (uint i = 0; i < m_pDef->GetVarNames().size(); ++i)
		m_aVariables.insert(VarPair(m_pDef->GetVarNames()[i], IBObject()));

	ResolveVariableFromPostCond(m_aPostCond.back());

	m_pDef->CreateOwnedVariables(this);

	if (IsResolved())
	{
		m_eState = IBA_State::IBA_Resolved;
		FinalizeCreation();
	}
	else
	{
		m_eState = IBA_State::IBA_Unresolved;

		for (VarMap::iterator it = m_aVariables.begin(); it != m_aVariables.end(); ++it)
		{
			const IBObject& Obj = it->second;
			if (Obj.GetUserData() == nullptr)
				m_aPotentialVariables.insert(PotentialVarPair(it->first, vector<IBObject>()));
		}

		m_pDef->CompleteVariables(this);
	}

	m_pDef->PostCreated(this);
}

IBAction::IBAction(const class IBAction* pOrig)
	: m_pDef(pOrig->m_pDef)
	, m_pPlanner(pOrig->m_pPlanner)
	, m_eState(IBA_Created)
	, m_pPostNode(pOrig->m_pPostNode)
	, m_pPreNode(nullptr)
	, m_aPostCond(pOrig->m_aPostCond)
	, m_pUserData(nullptr)
{
	for (VarMap::const_iterator it = pOrig->m_aVariables.begin(); it != pOrig->m_aVariables.end(); ++it)
	{
		m_aVariables.insert(VarPair(it->first, it->second));
	}

	for (IBFact* pFact : pOrig->m_aAdditionalPostCond)
	{
		m_aAdditionalPostCond.push_back(pFact->Clone());
	}
}

bool IBAction::CheckVariables() const
{
	for (VarMap::const_iterator itA = m_aVariables.begin(); itA != m_aVariables.end(); ++itA)
	{
		VarMap::const_iterator itB = itA;
		for (++itB; itB != m_aVariables.end(); ++itB)
		{
			if (itA->second == itB->second)
				return false;
		}
	}

	return true;
}

void IBAction::FinalizeCreation()
{
	// Fill m_aAdditionalPostCond with rest
	for (uint32 i = 0; i < m_pDef->GetPostCondDef().size(); ++i)
	{
		const IBFactCondDef& oPostCondDef = m_pDef->GetPostCondDef()[i];
		ASSERT(oPostCondDef.m_pFactDef->GetDegree() == oPostCondDef.m_aLinkNames.size());

		IBFact* pAddPostCond = oPostCondDef.m_pFactDef->Instanciate(oPostCondDef.m_bInverted, nullptr);
		pAddPostCond->ResolveVariableFromCond(this, oPostCondDef);

		bool found = false;

		// if pAddPostCond found in m_aPostCond -> delete and skip
		for (uint32 j = 0; j < m_aPostCond.size(); ++j)
		{
			const IBFact* pPostCond = m_aPostCond[j];
			if (pPostCond->IsEqual(pAddPostCond))
			{
				found = true;
				break;
			}
		}

		// if pAddPostCond found in m_aAdditionalPostCond -> delete and skip
		for (uint32 j = 0; !found && j < m_aAdditionalPostCond.size(); ++j)
		{
			const IBFact* pPostCond = m_aAdditionalPostCond[j];
			if (pPostCond->IsEqual(pAddPostCond))
			{
				found = true;
				break;
			}
		}

		if (found)
		{
			delete pAddPostCond;
			continue;
		}

		// if pAddPostCond found opposite in m_pPostNode
		//  equal -> Add To m_aPostCond
		for (FactSet::iterator it = m_pPostNode->GetFacts().begin(); it != m_pPostNode->GetFacts().end(); ++it)
		{
			IBFact* pPostCond = *it;
			if (pPostCond->IsEqual(pAddPostCond))
			{
				m_aPostCond.push_back(pPostCond);
				delete pAddPostCond;
				pAddPostCond = nullptr;
				break;
			}
		}

		if (pAddPostCond != nullptr && m_pPostNode->CheckCompatibility(pAddPostCond) == false)
			m_eState = IBA_Impossible;

		if (pAddPostCond != nullptr)
			m_aAdditionalPostCond.push_back(pAddPostCond);
	}

	// create Pre Node
	m_pPreNode = new IBNode(m_pPlanner, this);

	// Add pre cond in PreNode
	for (uint i = 0; i < m_pDef->GetPreCondDef().size(); ++i)
	{
		const IBFactCondDef& oPreCondDef = m_pDef->GetPreCondDef()[i];
		ASSERT(oPreCondDef.m_pFactDef->GetDegree() == oPreCondDef.m_aLinkNames.size());

		IBFact* pPreCond = oPreCondDef.m_pFactDef->Instanciate(oPreCondDef.m_bInverted, m_pPreNode);

		pPreCond->ResolveVariableFromCond(this, oPreCondDef);

		// skip if already in PreNode
		for (FactSet::iterator it = m_pPreNode->GetFacts().begin(); it != m_pPreNode->GetFacts().end(); ++it)
		{
			IBFact* pPreFact = *it;
			if (pPreFact->IsEqual(pPreCond))
			{
				delete pPreCond;
				pPreCond = nullptr;
				break;
			}
		}

		if (pPreCond != nullptr)
			m_pPreNode->AddFact(pPreCond);
	}

	// Add PostNode cond not resolved to PreNode
	for (FactSet::const_iterator it = m_pPostNode->GetFacts().begin(); it != m_pPostNode->GetFacts().end(); ++it)
	{
		IBFact* pFact = *it;

		if (pFact->IsTrue())
			continue;

		bool found = false;

		for (uint32 i = 0; i < m_aPostCond.size(); ++i)
		{
			if (m_aPostCond[i] == pFact)
			{
				found = true;
				break;
			}
		}

		if (found)
			continue;

		for (FactSet::iterator it = m_pPreNode->GetFacts().begin(); it != m_pPreNode->GetFacts().end(); ++it)
		{
			IBFact* pPreFact = *it;

			if (pPreFact->IsEqual(pFact))
			{
				found = true;
				break;
			}
		}

		if (found)
			continue;

		IBFact* copy = pFact->Clone();
		copy->m_aCauseAction.clear();
		copy->m_pNodeOwner = m_pPreNode;
		m_pPreNode->AddFact(copy);
	}

	if (m_pPreNode->CheckInnerCompatibility() == false)
		m_eState = IBA_State::IBA_Impossible;

	m_pPreNode->UpdateDuplicats();
}

IBAction::~IBAction()
{
	if (m_pPreNode != nullptr)
		delete m_pPreNode;

	for (uint32 i = 0; i < m_aAdditionalPostCond.size() ; ++i)
		delete m_aAdditionalPostCond[i];
}

void IBAction::Destroy()
{
	m_eState = IBA_State::IBA_Destroyed;

	for (uint32 i = 0; i < m_aAdditionalPostCond.size(); ++i)
		m_aAdditionalPostCond[i]->Destroy();

	if (m_pPreNode != nullptr)
		m_pPreNode->Destroy();
}

const IBObject* IBAction::GetVariable(const string& name) const
{
	VarMap::const_iterator it = m_aVariables.find(name);
	return (it == m_aVariables.end() ? nullptr : &(it->second));
}

void IBAction::SetVariable(const string& var_name, const IBObject& obj)
{
	VarMap::iterator it = m_aVariables.find(var_name);
	if (it != m_aVariables.end())
	{
		it->second = obj;
	}
}

void IBAction::SetVariable(const string& var_name, const string& obj_name, void* user_data)
{
	VarMap::iterator it = m_aVariables.find(var_name);
	if (it != m_aVariables.end())
	{
		it->second.SetName(obj_name);
		it->second.SetUserData(user_data);
	}
}

void IBAction::AddPotentialVariable(const string& var_name, const string& obj_name, void* user_data)
{
	PotentialVarMap::iterator it = m_aPotentialVariables.find(var_name);

	if (it == m_aPotentialVariables.end())
	{
		vector<class IBObject> aObj;
		aObj.push_back(IBObject(obj_name, user_data));
		m_aPotentialVariables.insert(PotentialVarPair(var_name, aObj));
	}
	else
	{
		it->second.push_back(IBObject(obj_name, user_data));
	}
}

void IBAction::GetPotentialVariable(const string& var_name, vector<IBObject>& aObj) const
{
	PotentialVarMap::const_iterator it = m_aPotentialVariables.find(var_name);

	if (it == m_aPotentialVariables.end())
		aObj = it->second;
}

uint32 IBAction::GetPotentialVariableCount(const string& var_name) const
{
	PotentialVarMap::const_iterator it = m_aPotentialVariables.find(var_name);
	return (it == m_aPotentialVariables.end() ? 0 : it->second.size());
}


void IBAction::ResolveVariableFromPostCond(const IBFact* pPostCond)
{
	const IBFactCondDef* pCond = m_pDef->FindPostCond(pPostCond->GetFactDef()->GetName());

	for (uint i = 0; i < pCond->m_aLinkNames.size(); ++i)
	{
		const IBObject* pObj = pPostCond->GetVariable(pCond->m_aLinkNames[i].m_sCondVarName);
		if (pObj)
			SetVariable(pCond->m_aLinkNames[i].m_sActionVarName, pObj->GetName(), pObj->GetUserData());
	}
}

bool IBAction::IsResolved() const
{
	for (VarMap::const_iterator it = m_aVariables.begin(); it != m_aVariables.end(); ++it)
	{
		const IBObject& Obj = it->second;
		if (Obj.GetUserData() == nullptr)
			return false;
	}

	return true;
}

float IBAction::GetCost() const
{
	if (m_eState == IBA_Impossible)
		return FLT_MAX;

	float fValue = m_pDef->GetCost(this);

	return fValue;
}

float IBAction::GetTotalCost() const
{
	float fTotal = GetCost();

	if (m_pPostNode != nullptr && m_pPostNode->GetAction() != nullptr)
		fTotal += m_pPostNode->GetAction()->GetTotalCost();

	return fTotal;
}

IBPlanner* IBAction::GetPlanner()
{
	return m_pPlanner;
}

bool IBAction::IsChildOf(const IBFact* pFact) const
{
	for (uint32 j = 0; j < m_aPostCond.size(); ++j)
	{
		IBFact* pPostCond = m_aPostCond[j];

		if (pPostCond == pFact)
			return true;
	}

	if (m_pPostNode == nullptr)
		return false;

	if (m_pPostNode->GetAction() == nullptr)
		return false;

	return m_pPostNode->GetAction()->IsChildOf(pFact);
}

void IBAction::Update()
{
	if (m_eState == IBA_State::IBA_Unresolved)
	{
		if (m_aPotentialVariables.size() > 0)
		{
			PotentialVarMap::iterator it = m_aPotentialVariables.begin();
			if (it->second.size() > 0)
			{
				const string& sVarName = it->first;
				IBObject sVarObj = it->second.back();
				it->second.pop_back();

				PotentialVarMap NewPotentialVarMap(++it, m_aPotentialVariables.end());
				CloneWithVar(sVarName, sVarObj, NewPotentialVarMap);
			}
			else
			{
				m_aPotentialVariables.erase(it);
			}
		}
		else
		{
			Destroy();
		}
	}

	if (m_eState == IBA_State::IBA_Resolved)
		m_pDef->Update(this);

	if (m_pPreNode != nullptr)
		m_pPreNode->Update();
}

void IBAction::CloneWithVar(const string& sVarName, const IBObject& oVarObj)
{
	PotentialVarMap aPotentialVarMap;
	CloneWithVar(sVarName, oVarObj, aPotentialVarMap);
}

void IBAction::CloneWithVar(const string& sVarName, const IBObject& oVarObj, const PotentialVarMap& aPotentialVarMap)
{
	IBAction* pAction = new IBAction(this);

	pAction->SetVariable(sVarName, oVarObj);
	pAction->m_aPotentialVariables = aPotentialVarMap;

	for (uint32 j = 0; j < m_aPostCond.size(); ++j)
	{
		IBFact* pPostCond = m_aPostCond[j];
		pPostCond->AddCauseAction(pAction);
	}

	if (pAction->IsResolved())
	{
		if (pAction->CheckVariables())
		{
			pAction->m_eState = IBA_State::IBA_Resolved;
			pAction->FinalizeCreation();
		}
		else
		{
			pAction->SetState(IBA_State::IBA_Impossible);
		}
	}
	else
	{
		pAction->m_eState = IBA_State::IBA_Unresolved;

		for (VarMap::iterator it = m_aVariables.begin(); it != m_aVariables.end(); ++it)
		{
			const IBObject& Obj = it->second;
			if (Obj.GetUserData() == nullptr)
				pAction->m_aPotentialVariables.insert(PotentialVarPair(it->first, vector<IBObject>()));
		}

		m_pDef->CompleteVariables(pAction);
	}

	m_pDef->PostCreated(this);
}

void IBAction::Start()
{
	//LOG("Action %s Started\n", m_pDef->GetName().c_str());

	if (m_pDef->Start(this))
		m_eState = IBA_Active;
}

void IBAction::Interrupt()
{
	if (m_eState == IBA_Active)
		m_pDef->Interrupt(this);
}


