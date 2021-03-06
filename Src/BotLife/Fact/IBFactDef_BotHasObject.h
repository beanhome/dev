#ifndef __IBFACTDEF_BOTHASOBJECT_H__
#define __IBFACTDEF_BOTHASOBJECT_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_BotHasObject : public IBFactDef
{
	public:
		IBFactDef_BotHasObject(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_BotHasObject();

		virtual IBF_Result		Test(const class IBFact* pFact) const override;
};

#endif
