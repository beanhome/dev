#ifndef __IBFACTDEF_OBJECTATPOS_H__
#define __IBFACTDEF_OBJECTATPOS_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_ObjectAtPos : public IBFactDef
{
	public:
		IBFactDef_ObjectAtPos(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_ObjectAtPos();

		virtual IBF_Result		Test(const class IBFact* pFact) const override;
};

#endif
