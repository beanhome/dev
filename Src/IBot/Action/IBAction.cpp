#include "IBAction.h"
#include "IBActionDef.h"

#include "World/IBCube.h"

#include "CanvasBase.h"


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



void IBAction::Print(int tab) const
{
	m_pDef->Print(m_aVariables, tab);
	PrintVar(m_aVariables, tab);

	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		m_aPreCond[i]->Print(tab+1);
	}
}

void IBAction::PrintVar(const IBAction::VarMap& aUserData, int tab) const
{
	for (IBAction::VarMap::const_iterator it = aUserData.begin() ; it != aUserData.end() ; ++it)
	{
		for (int i=0 ; i<tab ; ++i)
			LOG("\t");

		LOG("  var %s 0x%x %s\n", it->first.c_str(), it->second, ( it->second != NULL ? ((IBCube*)it->second)->GetName().c_str() : "NULL" ));
	}
}

void IBAction::Draw(CanvasBase& canva, int& x, int& y, const IBFact* pFact) const
{
	Color color(256, 256, 128);

	uint i=0;

	for (i=0 ; i<m_aPostCond.size() ; ++i)
		if (m_aPostCond[i] == pFact)
			break;

	assert(i < m_aPostCond.size());

	int max_in = max(m_aPreCond.size(), m_aPostCond.size());

	int title = 18;
	int offset = 22;
	int w = 256;
	int h = title + max_in * offset;
	int offset_left = (h - title)/m_aPreCond.size();
	int offset_right = (h - title)/m_aPostCond.size();
	int space = 64;
	int sq_size = 10;
	int title_space = 3;

	canva.DrawLine(x, y, x-space+sq_size, y, Color(255, 255, 255));

	x -= space + w/2;
	int top = y - (title + i*offset_right + offset_right/2);
	y = top + h/2;
	top += title;

	canva.DrawRect(x-w/2, y-h/2, w, h, color);
	canva.DrawLine(x-w/2, y-h/2+title, x+w/2-1, y-h/2+title, color);

	canva.Print(x, top-title/2, canva.GetPrintFont(), title-title_space*2, Center, color, "%s", m_pDef->GetName().c_str());

	int left = x-w/2;
	int right = x+w/2;

	for (uint j=0 ; j<m_aPreCond.size() ; ++j)
	{
		x = left - sq_size;
		y = top+j*offset_left+offset_left/2;

		canva.DrawRect(x, y-sq_size/2, sq_size, sq_size, color);
		m_aPreCond[j]->Draw(canva, x, y);
	}

	for (uint j=0 ; j<m_aPostCond.size() ; ++j)
		canva.DrawRect(right, top+j*offset_right+offset_right/2-sq_size/2, sq_size, sq_size, color);
}


