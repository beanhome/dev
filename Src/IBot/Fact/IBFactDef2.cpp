#include "IBFactDef2.h"
#include "IBFact2.h"


IBFactDef2::IBFactDef2()
{
}

IBFactDef2::~IBFactDef2()
{
}

IBFact* IBFactDef2::Instanciate(void* pUserData1, void* pUserData2)
{
	return new IBFact2(this, pUserData1, pUserData2);
}
