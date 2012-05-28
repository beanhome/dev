#ifndef __IBFACTDEF_ISFREE_H__
#define __IBFACTDEF_ISFREE_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_IsFree : public IBFactDef
{
	public:
		IBFactDef_IsFree(const string& name);
		virtual ~IBFactDef_IsFree();

		virtual void			ResolveVariable(vector<void*>& aUserData);

		IBF_Result				Test(const vector<void*>& aUserData);

		virtual void			Print(const vector<void*>& aUserData, int tab) const;

	private:
};

#endif
