#ifndef __IBFACTDEF_BOTATPOS_H__
#define __IBFACTDEF_BOTATPOS_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_BotAtPos : public IBFactDef
{
	public:
		IBFactDef_BotAtPos(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_BotAtPos();

		virtual IBF_Result		Test(const class IBFact* pFact) const override;
};

#endif
