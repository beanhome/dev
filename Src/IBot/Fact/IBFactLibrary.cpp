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
	const char* prefix = "IBFactDef_";
	const uint len = strlen(prefix);
	uint offset = (strncmp(name.c_str(), prefix, len) == 0 ? len : 0);

	m_oMap.insert(FactDefPair(name.c_str()+offset, pFactDef));
}

IBFactDef* IBFactLibrary::GetFactDef(const string& name)
{
	const char* prefix = "IBFactDef_";
	const uint len = strlen(prefix);
	uint offset = (strncmp(name.c_str(), prefix, len) == 0 ? len : 0);

	FactDefMap::iterator it = m_oMap.find(name.c_str()+offset);
	return (it != m_oMap.end() ? it->second : NULL);
}
