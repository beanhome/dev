#include "IBFactDef.h"
#include "IBFact.h"
#include "IBPlanner.h"
#include "World\IBObject.h"

char* IBF_ResultString[IBF_Result_MAX] =
{
	"OK",
	"FAIL",
	"UNKNOW",
	"IMPOSSIBLE",
	"DELETE",
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

void IBFactDef::GetData(const vector<IBObject*>& aUserData, string& sData) const
{
	sData.clear();
	for (uint i=0 ; i<aUserData.size() ; ++i)
	{
		sData += aUserData[i]->GetData();

		if (i<aUserData.size()-1)
			LOG(", ");
	}
}

string IBFactDef::GetData(const vector<IBObject*>& aUserData) const
{
	string sData;
	GetData(aUserData, sData);	
	return sData;
}


