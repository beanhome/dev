#ifndef __IBFactDef_BotAtPos_H__
#define __IBFactDef_BotAtPos_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_BotAtPos : public IBFactDef
{
	public:
		IBFactDef_BotAtPos(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_BotAtPos();

		virtual void			ResolveVariable(vector<IBObject*>& aUserData);

		virtual IBF_Result		Test(const vector<IBObject*>& aUserData);

	private:
};

#endif
