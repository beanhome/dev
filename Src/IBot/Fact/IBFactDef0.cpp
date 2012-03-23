#include "IBFactDef0.h"
#include "IBFact0.h"


IBFactDef0::IBFactDef0()
{

}

IBFactDef0::~IBFactDef0()
{

}


IBFact* IBFactDef0::Instanciate()
{
	return new IBFact0(this);
}
