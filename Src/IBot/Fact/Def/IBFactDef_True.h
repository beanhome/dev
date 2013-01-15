#ifndef __IBFACTDEF_TRUE_H__
#define __IBFACTDEF_TRUE_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_True : public IBFactDef
{
	public:
		IBFactDef_True(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_True();

		IBF_Result			Test(const vector<void*>& aUserData) { return IBF_OK; }
};

#endif
