#include "IBPlanner.h"


#include "IBFactDef_True.h"
#include "IBFactDef_False.h"
#include "IBFactDef_Bool.h"

#include "IBActionDef_BoolToBool.h"


IBPlanner::IBPlanner()
{
	InitFactLibrary();
	InitActionLibrary();
}

IBPlanner::~IBPlanner()
{

}

#define REGISTER_FACT(a) m_oFactLibrary.RegisterFactDef(#a, new a())

void IBPlanner::InitFactLibrary()
{
	REGISTER_FACT(IBFactDef_True);
	REGISTER_FACT(IBFactDef_False);
	REGISTER_FACT(IBFactDef_Bool);
}

#define REGISTER_ACTION(a) m_oActionLibrary.RegisterActionDef(#a, new a(this))

void IBPlanner::InitActionLibrary()
{
	REGISTER_ACTION(IBActionDef_BoolToBool);
}
