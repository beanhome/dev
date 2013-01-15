#ifndef __IBFACTDEF_ISONTABLE_BOOL_H__
#define __IBFACTDEF_ISONTABLE_BOOL_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_IsOnTable : public IBFactDef
{
	public:
		IBFactDef_IsOnTable(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_IsOnTable();

		IBF_Result			Test(const vector<void*>& aUserData);

		virtual void		ResolveVariable(vector<void*>& aUserData);

		virtual void		Print(const vector<void*>& aUserData, int tab) const;

	private:
};

#endif
