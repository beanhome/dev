#ifndef __IBFACTDEF_PROPISMOVABLE_H__
#define __IBFACTDEF_PROPISMOVABLE_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_PropIsMovable : public IBFactDef
{
	public:
		IBFactDef_PropIsMovable(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_PropIsMovable();

		virtual IBF_Result		Test(const class IBFact* pFact) const override;
};


#endif
