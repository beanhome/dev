#include "IBActionDef.h"
#include "World/IBObject.h"
#include "IBPlanner.h"
#include "IBAction.h"

IBActionDef::IBActionDef(const string& name, IBPlanner* pPlanner)
	: m_sName(name)
	, m_pPlanner(pPlanner)
{
	static const char* prefix = "IBActionDef_";
	static const uint len = strlen(prefix);
	uint offset = (strncmp(name.c_str(), prefix, len) == 0 ? len : 0);

	m_sName = name.c_str() + offset;
}

IBActionDef::~IBActionDef()
{
}

void IBActionDef::AddVariable(const char* name)
{
	m_aVarNames.push_back(name);
}

void IBActionDef::AddPreCondition(const char* name, bool bTrue, ...)
{
	IBFactDef* pFact = m_pPlanner->GetFactDef(name);

	assert(pFact != nullptr);

	if (pFact != nullptr)
	{
		uint n = pFact->GetDegree();

		va_list vl;
		va_start(vl, bTrue);

		IBFactCondDef oCond(pFact, !bTrue);

		if (n == 1)
		{
			char* arg = va_arg(vl, char*);
			oCond.AddLink(arg);
		}
		else
		{
			for (uint i = 0; i < n; ++i)
			{
				char* fact_var_name = va_arg(vl, char*);
				char* action_var_name = va_arg(vl, char*);
				oCond.AddLink(fact_var_name, action_var_name);
			}
		}

		m_aPreCondDef.push_back(oCond);

		va_end(vl);
	}
}

void IBActionDef::AddPostCondition(const char* name, bool bTrue, ...)
{
	IBFactDef* pFact = m_pPlanner->GetFactDef(name);

	assert(pFact != nullptr);

	if (pFact != nullptr)
	{
		uint n = pFact->GetDegree();

		va_list vl;
		va_start(vl, bTrue);

		IBFactCondDef oCond(pFact, !bTrue);

		if (n == 1)
		{
			char* arg = va_arg(vl, char*);
			oCond.AddLink(arg);
		}
		else
		{
			for (uint i = 0; i < n; ++i)
			{
				char* fact_var_name = va_arg(vl, char*);
				char* action_var_name = va_arg(vl, char*);
				oCond.AddLink(fact_var_name, action_var_name);
			}
		}

		m_aPostCondDef.push_back(oCond);

		va_end(vl);
	}
}

IBAction* IBActionDef::Instanciate(IBFact* pPostCond)
{
	// Instantiation
	IBAction* pAction = m_pPlanner->InstanciateAction(this, pPostCond);
	pAction->Create();

	return pAction;
}

const IBFactCondDef* IBActionDef::FindPostCond(const string& sPostCondName) const
{
	for (uint i = 0; i < m_aPostCondDef.size(); ++i)
	{
		if (m_aPostCondDef[i].GetName() == sPostCondName)
			return &m_aPostCondDef[i];
	}

	return nullptr;
}

