#ifndef __IBPLANNER_BL_H__
#define __IBPLANNER_BL_H__

#include "IBPlanner.h"

class IBPlanner_BL : public IBPlanner
{
	public:
		IBPlanner_BL(void* pOwner);
		virtual ~IBPlanner_BL();

		virtual IBAction*		InstanciateAction(const class IBActionDef* pDef, IBFact* pPostCond);
		virtual bool				AreCompatible(const class IBFact* A, const class IBFact* B) const;
};


#endif
