#ifndef __IBFACTDEF_BOTISEMPTY_H__
#define __IBFACTDEF_BOTISEMPTY_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_BotIsEmpty : public IBFactDef
{
	public:
		IBFactDef_BotIsEmpty(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_BotIsEmpty();

		virtual void			ResolveVariable(vector<void*>& aUserData);

		virtual IBF_Result		Test(const vector<void*>& aUserData);

		virtual void			Print(const vector<void*>& aUserData, int tab) const;

	private:
};

#endif
