#include "IBFactDef.h"
#include "IBFact.h"

char* IBF_ResultString[IBF_Result_MAX] =
{
	"OK",
	"FAIL",
	"UNKNOW",
};


IBFactDef::IBFactDef(const string& name, uint iDegree)
	: m_sName(name)
	, m_iDegree(iDegree)
{

}

IBFactDef::~IBFactDef()
{

}

IBFact* IBFactDef::Instanciate(vector<void*> aUserData)
{
	assert(aUserData.size() == m_iDegree);

	return new IBFact(this, aUserData);
}

void IBFactDef::Print(const vector<void*>& aUserData, int tab) const
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
