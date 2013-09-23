#include "IBAction.h"
#include "IBActionDef.h"
#include "IBPlanner.h"


const char*	IBAction::s_sStateString[State_MAX] =
{
	"Init",
	"Unresolved",
	"resolved",
	"Impossible",
	"Start",
	"Execute",
	"Abort",
	"End",
	"Finish",
	"Destroy",
	"Destroyed",
};


IBAction::IBAction(IBActionDef* pDef, IBFact* pPostCond1)
	: m_pDef(pDef)
	, m_eState(IBA_Init)
	, m_pUserData(NULL)
	, m_bToDelete(false)
{
	// create action variable
	for (uint i=0 ; i<pDef->GetVariables().size() ; ++i)
	{
		m_aVariables.insert(VarPair(pDef->GetVariables()[i], (IBObject*)NULL));
	}

	// create fact vector
	m_aPreCond.resize(pDef->GetPreCondDef().size(), NULL);
	m_aPostCond.resize(pDef->GetPostCondDef().size(), NULL);

	// instantiate pre cond
	for (uint i=0 ; i<pDef->GetPreCondDef().size() ; ++i)
	{
		const FactCondDef& oPreCondDef = pDef->GetPreCondDef()[i];
		ASSERT(oPreCondDef.m_pFactDef->GetDegree() == oPreCondDef.m_aVarName.size());

		vector<IBObject*> aUserData;
		aUserData.resize(oPreCondDef.m_pFactDef->GetDegree(), NULL);

		IBFact* pPreCond = oPreCondDef.m_pFactDef->Instanciate(this, aUserData);

		AddPreCond(i, pPreCond);
	}
}

IBAction::~IBAction()
{
	m_pDef->PreDestroy(m_aVariables);

	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		delete m_aPreCond[i];
	}

	for (uint i=0 ; i<m_aPostCond.size() ; ++i)
	{
		if (m_aPostCond[i] != NULL)
			m_aPostCond[i]->RemoveCauseAction(this);
	}
}

IBObject* IBAction::FindVariables(const string& name) const
{
	VarMap::const_iterator it = m_aVariables.find(name);
	return (it == m_aVariables.end() ? NULL : it->second);
}

void IBAction::SetVariable(const string& name, IBObject* val)
{
	VarMap::iterator it = m_aVariables.find(name);
	if (it != m_aVariables.end() && it->second != val)
	{
		it->second = val;

		// Affecte data to pre cond
		AffectPreCondVariable(name, val);
		
		// Affecte data to pre cond // TOCHECK
		//AffectPostCondVariable(name, val);
	}
}



void IBAction::AddPostCond(uint i, IBFact* pPostCond)
{
	assert(i<m_aPostCond.size());
	m_aPostCond[i] = pPostCond;
	pPostCond->AddCauseAction(this);

	// resolve name variable from post cond
	ResolveVariableName(i, pPostCond);
}

void IBAction::RemPostCond(IBFact* pPostCond)
{
	pPostCond->RemoveCauseAction(this);

	for (vector<IBFact*>::iterator it = m_aPostCond.begin() ; it != m_aPostCond.end() ; ++it)
	{
		if (*it == pPostCond)
		{
			m_aPostCond.erase(it);
			break;
		}
	}
}


void IBAction::AddPreCond(uint i, IBFact* pPreCond)
{
	ASSERT(i<m_aPreCond.size());
	m_aPreCond[i] = pPreCond;
	pPreCond->SetEffectAction(this);
}

void IBAction::AddPreCond(IBFact* pPreCond)
{
	m_aPreCond.push_back(pPreCond);
	pPreCond->SetEffectAction(this);
}

const FactCondDef& IBAction::GetPostConfDefFromFact(IBFact* pPostCond) const
{
	ASSERT(false); // unused

	static FactCondDef NullDef(NULL);

	for (uint i=0 ; i<m_aPostCond.size() ; ++i)
	{
		if (pPostCond == m_aPostCond[i])
			return m_pDef->GetPostCondDef()[i];
	}

	ASSERT(false);
	return NullDef;
}

const FactCondDef& IBAction::GetPreConfDefFromFact(IBFact* pPreCond) const
{
	ASSERT(false); // unused
	
	static FactCondDef NullDef(NULL);

	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		if (pPreCond == m_aPreCond[i])
			return m_pDef->GetPreCondDef()[i];
	}

	ASSERT(false);
	return NullDef;
}


// Resolve Variable data of Action from the post cond
void IBAction::ResolveVariableName(uint i, IBFact* pPostCond)
{
	FactCondDef* pPostCondDef = &m_pDef->GetPostCondDef()[i];

	assert(pPostCondDef->m_aVarName.size() == pPostCond->GetUserData().size());

	// for each post cond data
	for (uint k=0 ; k<pPostCondDef->m_aVarName.size() ; ++k)
	{
		// get name from post cond def
		const string& name = pPostCondDef->m_aVarName[k];

		// get data from post cond
		IBObject* pUserData = pPostCond->GetUserData()[k];

		// set data to variable
		SetVariable(name, pUserData);
	}
}

// Affect data to pre cond
void IBAction::AffectPreCondVariable(const string& name, IBObject* data)
{
	// for each pre cond
	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		// get pre fact
		IBFact* pPreFact = m_aPreCond[i];

		// get def
		const FactCondDef* pPreCondDef = &m_pDef->GetPreCondDef()[i];

		// for each var of pre cond
		for (uint j=0 ; j<pPreCondDef->m_aVarName.size() ; ++j)
		{
			// if correspond, set
			if (pPreCondDef->m_aVarName[j] == name)
			{
				pPreFact->SetVariable(j, data);
			}
		}
	}
}

void IBAction::AffectPostCondVariable(const string& name, IBObject* data)
{
	ASSERT(false);

	// for each post cond
	for (uint i=0 ; i<m_aPostCond.size() ; ++i)
	{
		// get post fact
		IBFact* pPostFact = m_aPostCond[i];

		// get def
		const FactCondDef* pPostCondDef = &m_pDef->GetPostCondDef()[i];

		// for each var of post cond
		for (uint j=0 ; j<pPostCondDef->m_aVarName.size() ; ++j)
		{
			// if correspond, set
			if (pPostCondDef->m_aVarName[j] == name)
			{
				pPostFact->SetVariable(j, data);
			}
		}
	}
}

/*
// Update Variable from post and pre condition
void IBAction::ResolvePreCond()
{
	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		IBFact* pPreFact = m_aPreCond[i];
		pPreFact->ResolveVariable();
	}

	SpreadPreCondVariable();
}
*/

// Update Variable from post and pre condition
void IBAction::SpreadVariable()
{
	ASSERT(false);

	UpdateVariableFromPostCond();
	SpreadPreCondVariable();
}

// Update Variable from post condition
void IBAction::UpdateVariableFromPostCond()
{
	// for each post cond
	for (uint i=0 ; i<m_aPostCond.size() ; ++i)
	{
		IBFact* pPostFact = m_aPostCond[i];
		if (pPostFact == NULL) continue;

		const FactCondDef* pPostCondDef = &m_pDef->GetPostCondDef()[i];

		// for each post cond variable
		for (uint j=0 ; j<pPostCondDef->m_aVarName.size() ; ++j)
		{
			const string& name = pPostCondDef->m_aVarName[j];

			// find action variable correspondence
			IBObject* pCurrentVar = FindVariables(name);
			IBObject* pPostVar = pPostFact->GetVariable(j);

			if (pCurrentVar != pPostVar)
			{
				SetVariable(name, pPostVar);
			}
		}
	}
}

// Update Variable from pre condition
void IBAction::SpreadPreCondVariable(IBFact* pPreCond)
{
	// for each pre cond
	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		IBFact* pPreFact = m_aPreCond[i];

		if (pPreCond != NULL && pPreCond != pPreFact)
			continue;

		const FactCondDef* pPreCondDef = &m_pDef->GetPreCondDef()[i];
		// for each pre cond variable
		for (uint j=0 ; j<pPreCondDef->m_aVarName.size() ; ++j)
		{
			const string& name = pPreCondDef->m_aVarName[j];

			// find action variable correspondence
			IBObject* pCurrentVar = FindVariables(name);
			IBObject* pPreVar = pPreFact->GetVariable(j);

			if (pCurrentVar == NULL && pPreVar != NULL)
			{
				SetVariable(name, pPreVar);
			}
			else if (pCurrentVar != NULL && pPreVar == NULL)
			{
				pPreFact->SetVariable(j, pCurrentVar);
			}
			else if (pCurrentVar != pPreVar)
			{
				ASSERT(false); // What to do ???
			}
		}
	}
}

void IBAction::PrepareToDelete()
{
	m_bToDelete = true;

	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		m_aPreCond[i]->PrepareToDelete();
	}
}


bool IBAction::IsReadyToDestroy()
{
	if (!m_bToDelete)
		return false;

	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		if (!m_aPreCond[i]->IsReadyToDelete())
			return false;
	}

	return true;
}

bool IBAction::IsReadyToDelete()
{
	return (IsReadyToDestroy() && GetState() == IBA_Destroyed);
}


IBF_Result IBAction::ResolvePreCond(IBPlanner* pPlanner, bool bExecute)
{
	/*
	map<float, IBFact*> pFactOrdered;

	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
		pFactOrdered.insert(pair<float, IBFact*>(m_aPreCond[i]->Evaluate(), m_aPreCond[i]));

	bool res = true;
	for (map<float, IBFact*>::iterator it = pFactOrdered.begin() ; it != pFactOrdered.end() ; ++it)
		res &= it->second->Resolve(pPlanner);
	*/

	int results[IBF_Result_MAX];

	for (uint i=0 ; i<IBF_Result_MAX ; ++i)	results[i] = 0;
	
	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		IBF_Result preres = m_aPreCond[i]->Resolve(pPlanner, bExecute);

		if (preres == IBF_FAIL)
			bExecute = false;

		results[preres]++;
	}

	if (results[IBF_DELETE] == m_aPreCond.size())
		return IBF_DELETE;

	if (results[IBF_IMPOSSIBLE] > 0)
		return IBF_IMPOSSIBLE;

	if (results[IBF_FAIL] > 0)
		return IBF_FAIL;

	if (results[IBF_OK] == m_aPreCond.size())
		return IBF_OK;

	if (results[IBF_UNKNOW] == 0)
		return IBF_RESOLVED;

	return IBF_UNKNOW;
}


IBAction::State IBAction::Resolve(IBPlanner* pPlanner, bool bExecute)
{
	IBF_Result res;

	bExecute &= Evaluate() < IBPlanner::s_fMaxActionDelay;

	switch(m_eState)
	{
		case IBA_Init:
			if (m_bToDelete)
				SetState(IBA_Destroy);
			else if (m_pDef->Init(this))
				SetState(IBA_Unresolved);
			else if (ResolvePreCond(pPlanner, bExecute) == IBF_IMPOSSIBLE)
				SetState(IBA_Impossible);
			break;

		case IBA_Unresolved:
		case IBA_Resolved:
			if (pPlanner->GetCurrentAction() == this)
				pPlanner->SetCurrentAction(NULL);
			if (m_bToDelete)
				SetState(IBA_Destroy);
			res = ResolvePreCond(pPlanner, bExecute);
			if (res == IBF_IMPOSSIBLE)
			{
				SetState(IBA_Impossible);
				PrepareToDelete();
			}
			else if (res == IBF_OK && bExecute && pPlanner->GetCurrentAction() == NULL)
			{
				pPlanner->SetCurrentAction(this);
				SetState(IBA_Start);
			}
			else if (res == IBF_OK || res == IBF_RESOLVED)
			{
				SetState(IBAction::IBA_Resolved);
			}
			break;

		case IBA_Impossible:
			if (m_bToDelete)
				SetState(IBA_Destroy);
			break;

		case IBA_Start:
			Start();
			if (m_bToDelete)
				SetState(IBA_Finish);
			else if (ResolvePreCond(pPlanner, bExecute) != IBF_OK)
				SetState(IBA_Unresolved);
			else if (m_pDef->Start(this))
				SetState(IBA_Execute);
			break;

		case IBA_Execute:
			Execute();
			if (m_bToDelete)
				SetState(IBA_Abort);
			else if (ResolvePreCond(pPlanner, bExecute) != IBF_OK)
				SetState(IBA_Unresolved);
			else if (m_pDef->Execute(this))
				SetState(IBA_Finish);
			break;

		case IBA_Finish:
			Finish();
			if (ResolvePreCond(pPlanner, bExecute) != IBF_OK)
				SetState(IBA_Unresolved);
			else if (m_pDef->Finish(this))
				SetState(IBA_Destroy);
			break;

		case IBA_Abort:
			/*if (ResolvePreCond(pPlanner, bExecute) != IBF_OK)
				SetState(IBA_Finish);
			else */if (m_pDef->Abort(this))
				SetState(IBA_Finish);
			break;

		case IBA_Destroy:
			if (pPlanner->GetCurrentAction() == this)
				pPlanner->SetCurrentAction(NULL);
			if (IsReadyToDestroy())
			{
				m_pDef->Destroy(this);
				SetState(IBA_Destroyed);
			}
			else
			{
				ResolvePreCond(pPlanner, bExecute);
			}
			break;

		case IBA_Destroyed:
			//LOG("IBA_Destroy\n");
			break;
	}

	return GetState();
}

bool IBAction::IsResolved() const
{
	switch (m_eState)
	{
		case IBA_Resolved:
		case IBA_Start:
		case IBA_Execute:
		case IBA_Abort:
		case IBA_End:
		case IBA_Finish:
			return true;
	}

	return false;
}


float IBAction::Evaluate() const
{
	float fValue = m_pDef->Evaluate(this);

	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		fValue += m_aPreCond[i]->Evaluate();
	}

	return fValue;
}

void IBAction::Start()
{
	//LOG("Action %s Started\n", m_pDef->GetName().c_str());
	m_iExecCount = 0;
}

void IBAction::Execute()
{
	//LOG("Action %s Execute %d\n", m_pDef->GetName().c_str(), m_iExecCount);
	m_iExecCount++;
}

void IBAction::Finish()
{
	//LOG("Action %s Finish %d\n", m_pDef->GetName().c_str(), m_iExecCount);
}

