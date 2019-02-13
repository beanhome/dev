#ifndef __IBFACTDEF_ISTOPOF_BOOL_H__
#define __IBFACTDEF_ISTOPOF_BOOL_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_IsTopOf : public IBFactDef
{
	public:
		IBFactDef_IsTopOf(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_IsTopOf();

		virtual IBF_Result				Test(const class IBFact* pFact) const override;
};

#endif
