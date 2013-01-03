#include "IBPlannerDebug.h"

#include "World\IBWorld.h"
#include "IBPlanner.h"
#include "Fact\IBFact.h"
#include "Action\IBAction.h"
#include "Action\IBActionDef.h"
#include "Fact\IBFactDef.h"

extern IBWorld g_oWorld;

IBPlannerDebug::IBPlannerDebug(const IBPlanner& oPlanner)
	: IBPlannerDisplay(oPlanner)
{}

IBPlannerDebug::~IBPlannerDebug()
{}

void IBPlannerDebug::DrawWorld()
{
	g_oWorld.Print();
}

void IBPlannerDebug::DrawGraph()
{
	PrintPlanner(m_oPlanner);
}

void IBPlannerDebug::PrintPlanner(const IBPlanner& oPlanner) const
{
	LOG("\n");
	LOG("Plan : \n");
	for (FactSet::const_iterator it = oPlanner.GetGoals().begin() ; it != oPlanner.GetGoals().end() ; ++it)
	{
		IBFact* pFact = *it;

		PrintFact(*pFact, 0);
	}
	LOG("\n");
}

void IBPlannerDebug::PrintAction(const IBAction& oAction, int tab) const
{
	oAction.GetDef()->Print(oAction.GetVariables(), tab);

	for (IBAction::VarMap::const_iterator it = oAction.GetVariables().begin() ; it != oAction.GetVariables().end() ; ++it)
	{
		for (int i=0 ; i<tab ; ++i)
			LOG("\t");

		LOG("  var %s 0x%x %s\n", it->first.c_str(), it->second, ( it->second != NULL ? ((IBCube*)it->second)->GetName().c_str() : "NULL" ));
	}

	for (uint i=0 ; i<oAction.GetPreCond().size() ; ++i)
	{
		PrintFact(*oAction.GetPreCond()[i], tab+1);
	}
}


void IBPlannerDebug::PrintFact(const IBFact& oFact, int tab) const
{
	oFact.GetFactDef()->Print(oFact.GetUserData(), tab);

	for (int i=0 ; i<tab ; ++i) LOG("\t");
	LOG(IBF_ResultString[oFact.Test()]);
	LOG("\n");

	if (oFact.GetCauseAction() != NULL)
	{
		PrintAction(*oFact.GetCauseAction(), tab+1);
	}
}



