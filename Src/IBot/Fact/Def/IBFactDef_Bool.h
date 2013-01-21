#ifndef __IBFACTDEF_BOOL_H__
#define __IBFACTDEF_BOOL_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_Bool : public IBFactDef
{
	public:
		IBFactDef_Bool(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_Bool();

		IBF_Result			Test(const vector<IBObject*>& aUserData) { assert(aUserData.size() == 1); return (*((bool*)aUserData[0]) ? IBF_OK : IBF_FAIL); } 

	private:
};

#endif
