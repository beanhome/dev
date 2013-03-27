#ifndef __IBFACTDEF_PROPISUNBLOCK_H__
#define __IBFACTDEF_PROPISUNBLOCK_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_PropIsUnblock : public IBFactDef
{
	public:
		IBFactDef_PropIsUnblock(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_PropIsUnblock();

		virtual void			ResolveVariable(vector<IBObject*>& aUserData);

		virtual IBF_Result		Test(const vector<IBObject*>& aUserData);

	private:
};

class IBFactDef_PropIsBlock : public IBFactDef_PropIsUnblock
{
	public:
		IBFactDef_PropIsBlock(const string& name, IBPlanner* pPlanner) : IBFactDef_PropIsUnblock(name, pPlanner) {}

		virtual IBF_Result		Test(const vector<IBObject*>& aUserData) { return (IBFactDef_PropIsUnblock::Test(aUserData) == IBF_OK ? IBF_FAIL : IBF_OK); }
};

#endif
