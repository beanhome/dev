#ifndef __IBPLANNERDEBUG_H__
#define __IBPLANNERDEBUG_H__

#include "IBPlannerDisplay.h"

class IBPlannerDebug : public IBPlannerDisplay
{
	public:
		IBPlannerDebug(const class IBPlanner& oPlanner);
		virtual ~IBPlannerDebug();

	public:
		virtual void DrawGraph();

	private:
		void PrintPlanner(const class IBPlanner& oPlanner) const;
		void	 PrintNode(const class IBNode& oNode) const;
		void PrintAction(const class IBAction& oAction, int tab) const;
		void PrintFact(const class IBFact& oFact, int tab, bool counter=false) const;
};

#endif
