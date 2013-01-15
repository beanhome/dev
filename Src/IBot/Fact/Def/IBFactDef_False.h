#ifndef __IBFACTDEF_FALSE_H__
#define __IBFACTDEF_FALSE_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_False : public IBFactDef
{
	public:
		IBFactDef_False(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_False();

		IBF_Result			Test(const vector<void*>& aUserData) { return IBF_FAIL; }
};

#endif
