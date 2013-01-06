#ifndef __IBPLANNERTEST_H__
#define __IBPLANNERTEST_H__

#include "IBPlanner.h"

class IBPlannerTest : public IBPlanner
{
	public:
		IBPlannerTest();
		virtual ~IBPlannerTest();

	public:
		virtual void			InitFactLibrary();
		virtual void			InitActionLibrary();

};


#endif
