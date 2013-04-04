#include "IBPlannerDebug.h"

#include "IBPlanner.h"
#include "Fact/IBFact.h"
#include "Fact/IBFactDef.h"
#include "Action/IBAction.h"
#include "Action/IBActionDef.h"
#include "World/IBObject.h"

IBPlannerDebug::IBPlannerDebug(const IBPlanner& oPlanner)
	: IBPlannerDisplay(oPlanner)
{}

IBPlannerDebug::~IBPlannerDebug()
{}

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
	for (int i=0 ; i<tab ; ++i) LOG("\t");
	LOG("%s [%s]\n", oAction.GetDef()->GetName().c_str(), IBAction::s_sStateString[oAction.GetState()]);

	for (IBAction::VarMap::const_iterator it = oAction.GetVariables().begin() ; it != oAction.GetVariables().end() ; ++it)
	{
		for (int i=0 ; i<tab ; ++i)
			LOG("\t");

		LOG("  var %s %s\n", it->first.c_str(), ( it->second != NULL ? it->second->GetName().c_str() : "nil" ));
	}

	for (uint i=0 ; i<oAction.GetPreCond().size() ; ++i)
	{
		PrintFact(*oAction.GetPreCond()[i], tab+1);
	}
}


void IBPlannerDebug::PrintFact(const IBFact& oFact, int tab) const
{
	for (int i=0 ; i<tab ; ++i) LOG("\t");

	LOG("%s (", oFact.GetFactDef()->GetName().c_str());
	for (uint i=0 ; i<oFact.GetVariables().size() ; ++i)
	{
		LOG("%s", (oFact.GetVariable(i) != NULL ? oFact.GetVariable(i)->GetName().c_str() : "nil"));
		if (i<oFact.GetVariables().size()-1)
			LOG(", ");
	}
	LOG(")");
	LOG(" [");
	LOG(IBF_ResultString[oFact.Test()]);
	LOG("]\n");

	for (ActionSet::const_iterator it = oFact.GetCauseAction().begin() ; it != oFact.GetCauseAction().end() ; ++it)
	{
		IBAction* pAction = *it;

		PrintAction(*pAction, tab+1);
	}
}



