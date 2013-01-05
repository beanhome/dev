#ifndef __IBFACTDEF_ISTOPOF_BOOL_H__
#define __IBFACTDEF_ISTOPOF_BOOL_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_IsTopOf : public IBFactDef
{
	public:
		IBFactDef_IsTopOf(const string& name);
		virtual ~IBFactDef_IsTopOf();

		IBF_Result			Test(const vector<void*>& aUserData);

		virtual void		ResolveVariable(vector<void*>& aUserData);
	
		virtual void		Print(const vector<void*>& aUserData, int tab) const;

	private:
};

#endif
