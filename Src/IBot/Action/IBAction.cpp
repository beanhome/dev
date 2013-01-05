#include "IBAction.h"
#include "IBActionDef.h"

#include "World/IBCube.h"


IBAction::IBAction(IBActionDef* pDef)
	: m_pDef(pDef)
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

		vector<void*> aUserData;
		aUserData.resize(oPreCondDef.m_pFactDef->GetDegree(), NULL);

		assert(oPreCondDef.m_pFactDef->GetDegree() == oPreCondDef.m_aVarName.size());

		IBFact* pPreCond = new IBFact(oPreCondDef.m_pFactDef, aUserData);

		AddPreCond(i, pPreCond);
	}

}

IBAction::~IBAction()
{
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

void* IBAction::FindVariables(const string& name) const
{
	VarMap::const_iterator it = m_aVariables.find(name);
	return (it == m_aVariables.end() ? NULL : it->second);
}

void IBAction::SetVariable(const string& name, void* val)
{
	VarMap::iterator it = m_aVariables.find(name);
	if (it != m_aVariables.end() && it->second != val)
	{
		it->second = val;

		// Affecte data to pre cond
		AffectPreCondVariable(name, val);
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

void IBAction::AddPreCond(uint i, IBFact* pPreCond)
{
	assert(i<m_aPreCond.size());
	m_aPreCond[i] = pPreCond;
	pPreCond->SetEffectAction(this);
}

const FactCondDef& IBAction::GetPostConfDefFromFact(IBFact* pPostCond) const
{
	static FactCondDef NullDef(NULL);

	for (uint i=0 ; i<m_aPostCond.size() ; ++i)
	{
		if (pPostCond == m_aPostCond[i])
			return m_pDef->GetPostCondDef()[i];
	}

	assert(false);
	return NullDef;
}

const FactCondDef& IBAction::GetPreConfDefFromFact(IBFact* pPreCond) const
{
	static FactCondDef NullDef(NULL);

	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		if (pPreCond == m_aPreCond[i])
			return m_pDef->GetPreCondDef()[i];
	}

	assert(false);
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
		void* pUserData = pPostCond->GetUserData()[k];

		// set data to variable
		SetVariable(name, pUserData);
	}
}

// Affect data to pre cond
void IBAction::AffectPreCondVariable(const string& name, void* data)
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


void IBAction::ResolvePreCondVariable()
{
	// for each pre cond
	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		IBFact* pPreFact = m_aPreCond[i];
		const FactCondDef* pPreCondDef = &m_pDef->GetPreCondDef()[i];

		// resolve unfilled var
		pPreFact->ResolveVariable();
		
		// for each pre cond variable
		for (uint j=0 ; j<pPreCondDef->m_aVarName.size() ; ++j)
		{
			const string& name = pPreCondDef->m_aVarName[j];

			// find action variable correspondence
			void* pVar = FindVariables(name);

			if (pVar == NULL)
			{
				// set if null
				SetVariable(name, pPreFact->GetVariable(j));
			}
		}
	}
}


bool IBAction::Resolve(IBPlanner* pPlanner)
{
	bool res = true;
	
	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		res &= m_aPreCond[i]->Resolve(pPlanner);
	}

	return res;
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

