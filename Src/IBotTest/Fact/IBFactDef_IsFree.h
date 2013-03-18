#ifndef __IBFACTDEF_ISFREE_H__
#define __IBFACTDEF_ISFREE_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_IsFree : public IBFactDef
{
	public:
		IBFactDef_IsFree(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_IsFree();

		virtual void			ResolveVariable(vector<IBObject*>& aUserData);

		IBF_Result				Test(const vector<IBObject*>& aUserData);

	private:
};

#endif
