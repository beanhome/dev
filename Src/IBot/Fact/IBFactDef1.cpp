#include "IBFactDef1.h"
#include "IBFact1.h"


IBFactDef1::IBFactDef1()
{
}

IBFactDef1::~IBFactDef1()
{
}


IBFact* IBFactDef1::Instanciate(void* pUserData1)
{
	return new IBFact1(this, pUserData1);
}
