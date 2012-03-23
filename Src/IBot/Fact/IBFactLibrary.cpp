#include "IBFactLibrary.h"
#include "IBFactDef.h"


IBFactLibrary::IBFactLibrary()
{
}

IBFactLibrary::~IBFactLibrary()
{
	FactDefMap::iterator begin = m_oMap.begin();
	FactDefMap::iterator end = m_oMap.end();
	FactDefMap::iterator it;

	for (it=begin ; it!=end ; ++it)
	{
		delete it->second;
	}
}

void IBFactLibrary::RegisterFactDef(const string& name, IBFactDef* pFactDef)
{
	m_oMap.insert(FactDefPair(name, pFactDef));
}

IBFactDef* IBFactLibrary::GetFactDef(const string& name)
{
	FactDefMap::iterator it = m_oMap.find(name);
	return (it != m_oMap.end() ? it->second : NULL);
}
