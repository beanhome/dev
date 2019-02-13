#ifndef __IBFACTDEF_HASVALIDPATH_H__
#define __IBFACTDEF_HASVALIDPATH_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_HasValidPath : public IBFactDef
{
	public:
		IBFactDef_HasValidPath(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_HasValidPath();

		virtual IBF_Result		Test(const class IBFact* pFact) const override;
};

#endif
