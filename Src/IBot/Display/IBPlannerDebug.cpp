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
	PrintWorldChange(oPlanner.GetGoals());
	LOG("\n");
}

void	 IBPlannerDebug::PrintWorldChange(const IBWorldChange& oWorldChange) const
{
	for (FactSet::const_iterator it = oWorldChange.GetFacts().begin(); it != oWorldChange.GetFacts().end(); ++it)
	{
		IBFact* pFact = *it;
		PrintFact(*pFact, 0);
	}
}

void IBPlannerDebug::PrintAction(const IBAction& oAction, int tab) const
{
	for (int i=0 ; i<tab ; ++i) LOG("\t");
	LOG("%s [%s]\n", oAction.GetDef()->GetName().c_str(), IBA_StateString[oAction.GetState()]);

	for (VarMap::const_iterator it = oAction.GetVariables().begin() ; it != oAction.GetVariables().end() ; ++it)
	{
		for (int i=0 ; i<tab ; ++i)
			LOG("\t");

		LOG("  var %s %s\n", it->first.c_str(), it->second.GetName().c_str());
	}

	/*
	if (oAction.GetPreCond().size() > 0)
	{
		for (int i=0 ; i<tab ; ++i)	LOG("\t");
		LOG("  pre cond :\n");
	}
	for (uint i=0 ; i<oAction.GetPreCond().size() ; ++i)
	{
		PrintFact(*oAction.GetPreCond()[i], tab+1);
	}
	*/
}


void IBPlannerDebug::PrintFact(const IBFact& oFact, int tab, bool counter) const
{
	for (int i=0 ; i<tab ; ++i) LOG("\t");

	LOG("%s (", oFact.GetFactDef()->GetName().c_str());

	VarMap::const_iterator last = --oFact.GetVariables().end();
	for (VarMap::const_iterator it = oFact.GetVariables().begin(); it != oFact.GetVariables().end(); ++it)
	{
		LOG("%s: %s", it->first, it->second.GetName().c_str());
		if (it != last)
			LOG(", ");
	}
	LOG(")");
	LOG(" [");
	LOG(IBF_ResultString[oFact.Test()]);
	LOG("]\n");

	if (!counter)
	{
		for (ActionSet::const_iterator it = oFact.GetCauseAction().begin() ; it != oFact.GetCauseAction().end() ; ++it)
		{
			IBAction* pAction = *it;

			PrintAction(*pAction, tab+1);
		}
	}
}



