#ifndef __IBFACTDEF_PROPISBLOCK_H__
#define __IBFACTDEF_PROPISBLOCK_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_PropIsBlock : public IBFactDef
{
	public:
		IBFactDef_PropIsBlock(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_PropIsBlock();

		virtual IBF_Result		Test(const class IBFact* pFact) const override;
};

#endif
