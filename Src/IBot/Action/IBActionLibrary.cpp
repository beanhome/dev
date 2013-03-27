#include "IBActionLibrary.h"
#include "IBActionDef.h"
#include "Fact\IBFactDef.h"


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
	const char* prefix = "IBActionDef_";
	const uint len = strlen(prefix);
	uint offset = (strncmp(name.c_str(), prefix, len) == 0 ? len : 0);

	pActionDef->Define();
	m_oMap.insert(ActionDefPair(name.c_str()+offset, pActionDef));
}

IBActionDef* IBActionLibrary::GetActionDef(const string& name)
{
	const char* prefix = "IBActionDef_";
	const uint len = strlen(prefix);
	uint offset = (strncmp(name.c_str(), prefix, len) == 0 ? len : 0);

	ActionDefMap::iterator it = m_oMap.find(name.c_str()+offset);
	return (it != m_oMap.end() ? it->second : NULL);
}

IBActionDef* IBActionLibrary::FindActionDef(const string& factname)
{
	ActionDefMap::iterator begin = m_oMap.begin();
	ActionDefMap::iterator end = m_oMap.end();
	ActionDefMap::iterator it;

	for (it=begin ; it!=end ; ++it)
	{
		IBActionDef* pActionDef = it->second;

		for (uint i=0 ; i< pActionDef->GetPostCondDef().size() ; ++i)
		{
			IBFactDef* pFactDef = pActionDef->GetPostCondDef()[i].m_pFactDef;
			if (pFactDef->GetName() == factname)
			{
				return pActionDef;
			}
		}
	}

	return NULL;
}

IBAction* IBActionLibrary::FindActionDef(IBFact* pFact)
{
	ActionDefMap::iterator begin = m_oMap.begin();
	ActionDefMap::iterator end = m_oMap.end();
	ActionDefMap::iterator it;

	//IBAction* pBestAction = NULL;
	//float fBestValuate;

	for (it=begin ; it!=end ; ++it)
	{
		IBActionDef* pActionDef = it->second;

		for (uint i=0 ; i< pActionDef->GetPostCondDef().size() ; ++i)
		{
			IBFactDef* pFactDef = pActionDef->GetPostCondDef()[i].m_pFactDef;
			if (pFactDef->GetName() == pFact->GetFactDef()->GetName())
			{
				IBAction* pAction = pActionDef->Instanciate(pFact);

				/*
				float fValue = pAction->Evaluate();

				if (pBestAction == NULL)
				{
					pBestAction = pAction;
					fBestValuate = fValue;
				}
				else if (fValue > fBestValuate)
				{
					delete pBestAction;
					pBestAction = pAction;
					fBestValuate = fValue;
				}
				else
				{
					delete pBestAction;
				}

				break;
				*/
			}
		}
	}

	//return pBestAction;
	return NULL;
}

