#include "IBActionLibrary.h"
#include "IBActionDef.h"


IBActionLibrary::IBActionLibrary()
{
}

IBActionLibrary::~IBActionLibrary()
{
	ActionDefMap::iterator begin = m_oMap.begin();
	ActionDefMap::iterator end = m_oMap.end();
	ActionDefMap::iterator it;

	for (it=begin ; it!=end ; ++it)
	{
		delete it->second;
	}
}

void IBActionLibrary::RegisterActionDef(const string& name, IBActionDef* pActionDef)
{
	pActionDef->Define();
	m_oMap.insert(ActionDefPair(name, pActionDef));
}

IBActionDef* IBActionLibrary::GetActionDef(const string& name)
{
	ActionDefMap::iterator it = m_oMap.find(name);
	return (it != m_oMap.end() ? it->second : NULL);
}
