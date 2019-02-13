#ifndef __IBFACTDEF_BOTNEARPOS_H__
#define __IBFACTDEF_BOTNEARPOS_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_BotNearPos : public IBFactDef
{
	public:
		IBFactDef_BotNearPos(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_BotNearPos();

		virtual IBF_Result		Test(const class IBFact* pFact) const override;
};

#endif
