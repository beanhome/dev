#ifndef __IBFACTDEF_PROPISPICKABLE_H__
#define __IBFACTDEF_PROPISPICKABLE_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_PropIsPickable : public IBFactDef
{
	public:
		IBFactDef_PropIsPickable(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_PropIsPickable();

		virtual void			ResolveVariable(vector<IBObject*>& aUserData);

		virtual IBF_Result		Test(const vector<IBObject*>& aUserData);

	private:
};


#endif
