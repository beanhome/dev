#include "IBActionLibrary.h"
#include "IBActionDef.h"
#include "Fact/IBFactDef.h"

IBActionLibrary::IBActionLibrary()
{
}

IBActionLibrary::~IBActionLibrary()
{
	ActionDefMap::iterator begin = m_oMap.begin();
	ActionDefMap::iterator end = m_oMap.end();
	ActionDefMap::iterator it;

	for (it = begin; it != end; ++it)
	{
		delete it->second;
	}
}

void IBActionLibrary::RegisterActionDef(const string& name, IBActionDef* pActionDef)
{
	static const char* prefix = "IBActionDef_";
	static const uint len = strlen(prefix);
	uint offset = (strncmp(name.c_str(), prefix, len) == 0 ? len : 0);

	pActionDef->Define();
	m_oMap.insert(ActionDefPair(name.c_str() + offset, pActionDef));
	m_oSet.insert(pActionDef);
}

const ActionDefSet& IBActionLibrary::GetAllActionDef() const
{
	return m_oSet;
}

IBActionDef* IBActionLibrary::GetActionDef(const string& name) const
{
	static const char* prefix = "IBActionDef_";
	static const uint len = strlen(prefix);
	uint offset = (strncmp(name.c_str(), prefix, len) == 0 ? len : 0);

	ActionDefMap::const_iterator it = m_oMap.find(name.c_str() + offset);
	return (it != m_oMap.end() ? it->second : nullptr);
}

IBActionDef* IBActionLibrary::FindActionDef(const string& factname) const
{
	assert(false);

	ActionDefMap::const_iterator begin = m_oMap.begin();
	ActionDefMap::const_iterator end = m_oMap.end();
	ActionDefMap::const_iterator it;

	for (it = begin; it != end; ++it)
	{
		IBActionDef* pActionDef = it->second;

		for (uint i = 0; i < pActionDef->GetPostCondDef().size(); ++i)
		{
			IBFactDef* pFactDef = pActionDef->GetPostCondDef()[i].m_pFactDef;
			if (pFactDef->GetName() == factname)
			{
				return pActionDef;
			}
		}
	}

	return nullptr;
}

/*
IBAction* IBActionLibrary::FindActionDef(IBFact* pFact) const
{
	assert(false);

	ActionDefMap::const_iterator begin = m_oMap.begin();
	ActionDefMap::const_iterator end = m_oMap.end();
	ActionDefMap::const_iterator it;

	for (it = begin; it != end; ++it)
	{
		IBActionDef* pActionDef = it->second;

		for (uint i = 0; i < pActionDef->GetPostCondDef().size(); ++i)
		{
			IBFactDef* pFactDef = pActionDef->GetPostCondDef()[i].m_pFactDef;
			if (pFactDef->GetName() == pFact->GetFactDef()->GetName())
			{
				IBAction* pAction = pActionDef->Instanciate(pFact);
			}
		}
	}

	return nullptr;
}
*/