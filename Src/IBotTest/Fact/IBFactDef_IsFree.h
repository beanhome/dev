#ifndef __IBFACTDEF_ISFREE_H__
#define __IBFACTDEF_ISFREE_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_IsFree : public IBFactDef
{
	public:
		IBFactDef_IsFree(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_IsFree();

		virtual IBF_Result				Test(const class IBFact* pFact) const override;
};

#endif
