#include "IBFactDef.h"
#include "IBFact.h"
#include "IBPlanner.h"

char* IBF_ResultString[IBF_Result_MAX] =
{
	"OK",
	"FAIL",
	"UNKNOW",
};


IBFactDef::IBFactDef(const string& name, uint iDegree, IBPlanner* pPlanner)
	: m_sName(name)
	, m_iDegree(iDegree)
	, m_pPlanner(pPlanner)
{
	const char* prefix = "IBFactDef_";
	const uint len = strlen(prefix);
	uint offset = (strncmp(name.c_str(), prefix, len) == 0 ? len : 0);

	m_sName = name.c_str() + offset;
}

IBFactDef::~IBFactDef()
{

}

IBFact* IBFactDef::Instanciate(IBAction* pEffectAction, const vector<IBObject*> aUserData)
{
	assert(aUserData.size() == m_iDegree);
	return m_pPlanner->InstanciateFact(this, aUserData, pEffectAction);
}

void IBFactDef::Print(const vector<IBObject*>& aUserData, int tab) const
{
	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s", GetName().c_str());

	if (aUserData.size() > 0)
	{
		LOG(" (");
		for (uint i=0 ; i<aUserData.size() ; ++i)
		{
			LOG("0x%x", aUserData[i]);

			if (i<aUserData.size()-1)
				LOG(", ");
		}

		LOG(")");
	}


	LOG("\n");
}
