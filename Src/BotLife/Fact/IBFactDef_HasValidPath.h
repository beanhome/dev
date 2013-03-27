#ifndef __IBFACTDEF_HASVALIDPATH_H__
#define __IBFACTDEF_HASVALIDPATH_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_HasValidPath : public IBFactDef
{
	public:
		IBFactDef_HasValidPath(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_HasValidPath();

		virtual void			ResolveVariable(vector<IBObject*>& aUserData);

		virtual IBF_Result		Test(const vector<IBObject*>& aUserData);

	private:
};

#endif
