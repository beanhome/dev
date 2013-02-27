#ifndef __IBPLANNERDEBUG_H__
#define __IBPLANNERDEBUG_H__

#include "IBPlannerDisplay.h"

class IBPlanner;
class IBAction;
class IBFact;

class IBPlannerDebug : public IBPlannerDisplay
{
	public:
		IBPlannerDebug(const IBPlanner& oPlanner);
		virtual ~IBPlannerDebug();

	public:
		virtual void DrawGraph();

	private:
		void PrintPlanner(const IBPlanner& oPlanner) const;
		void PrintAction(const IBAction& oAction, int tab) const;
		void PrintFact(const IBFact& oFact, int tab) const;
};

#endif
