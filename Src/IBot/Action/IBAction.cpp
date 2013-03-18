#include "IBAction.h"
#include "IBActionDef.h"
#include "IBPlanner.h"


const char*	IBAction::s_sStateString[State_MAX] =
{
	"Init",
	"Unresolved",
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
		m_aVariables.insert(VarPair(pDef->GetVariables()[i], NULL));
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
	pPostCond->SetCauseAction(this);

	// resolve name variable from post cond
	ResolveVariableName(i, pPostCond);
}

void IBAction::RemPostCond(IBFact* pPostCond)
{
	pPostCond->SetCauseAction(NULL);

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

// Update Variable from post and pre condition
void IBAction::SpreadVariable()
{
	ASSERT(false);

	SpreadPostCondVariable();
	SpreadPreCondVariable();
}

// Update Variable from post condition
void IBAction::SpreadPostCondVariable()
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

			if (pCurrentVar == NULL && pPostVar != NULL)
			{
				SetVariable(name, pPostVar);
			}
			else if (pCurrentVar != NULL && pPostVar == NULL)
			{
				pPostFact->SetVariable(j, pCurrentVar);
			}
			else if (pCurrentVar != pPostVar)
			{
				ASSERT(false); // What to do ???
			}
		}
	}
}

// Update Variable from pre condition
void IBAction::SpreadPreCondVariable()
{
	// for each pre cond
	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		IBFact* pPreFact = m_aPreCond[i];
		// resolve unfilled var
		//pPreFact->ResolveVariable();

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


bool IBAction::IsReadyToDelete()
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


IBAction::State IBAction::Resolve(IBPlanner* pPlanner)
{
	bool res = true;
	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
		res &= m_aPreCond[i]->Resolve(pPlanner);

	if (pPlanner->GetCurrentAction() == NULL)
	{
		if (m_eState != IBA_Destroy && m_eState != IBA_Destroyed)
			pPlanner->SetCurrentAction(this);

		switch(m_eState)
		{
			case IBA_Init:
				if (m_bToDelete)
					SetState(IBA_Destroyed);
				else if (m_pDef->Init(this))
					SetState(IBA_Unresolved);
				else
					ResolvePreCond();
				break;

			case IBA_Unresolved:
				if (m_bToDelete)
					SetState(IBA_Finish);
				else if (res)
					SetState(IBA_Start);
				break;

			case IBA_Start:
				Start();
				if (m_bToDelete)
					SetState(IBA_Abort);
				else if (!res)
					SetState(IBA_Unresolved);
				else if (m_pDef->Start(this))
					SetState(IBA_Execute);
				break;

			case IBA_Execute:
				Execute();
				if (m_bToDelete)
					SetState(IBA_Abort);
				else if (!res)
					SetState(IBA_Unresolved);
				else if (m_pDef->Execute(this))
					SetState(IBA_Finish);
				break;

			case IBA_Finish:
				Finish();
				if (m_pDef->Finish(this))
				{
					PrepareToDelete();
					SetState(IBA_Destroy);
				}
				else
				{
					SetState(IBA_Unresolved);
				}
				break;

			case IBA_Abort:
				if (!res)
					SetState(IBA_Finish);
				else if (m_pDef->Abort(this))
					SetState(IBA_Finish);
				break;

			case IBA_Destroy:
				if (IsReadyToDelete())
				{
					m_pDef->Destroy(this);
					SetState(IBA_Destroyed);
				}
				break;

			case IBA_Destroyed:
				//LOG("IBA_Destroy\n");
				break;
		}
	}

	return GetState();
}

float IBAction::Valuate()
{
	float iCount = 0;

	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		if (m_aPreCond[i]->IsTrue())
			iCount++;
	}

	return (float)iCount / m_aPreCond.size();
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

