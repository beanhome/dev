#ifndef __IBFACTDEF_ISONTABLE_BOOL_H__
#define __IBFACTDEF_ISONTABLE_BOOL_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_IsOnTable : public IBFactDef
{
	public:
		IBFactDef_IsOnTable(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_IsOnTable();

		IBF_Result			Test(const vector<IBObject*>& aUserData);

		virtual void		ResolveVariable(vector<IBObject*>& aUserData);

	private:
};

#endif
