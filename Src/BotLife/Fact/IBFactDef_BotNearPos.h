#ifndef __IBFactDef_BotNearPos_H__
#define __IBFactDef_BotNearPos_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

// Fact BotNearPos
// degrees 2
// Param 1 : pos (IBVector2)
// Param 2 : dist (IBInt)

class IBFactDef_BotNearPos : public IBFactDef
{
	public:
		IBFactDef_BotNearPos(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_BotNearPos();

		virtual void			ResolveVariable(vector<IBObject*>& aUserData);

		virtual IBF_Result		Test(const vector<IBObject*>& aUserData);

		virtual void			Print(const vector<IBObject*>& aUserData, int tab) const;

	private:
};

#endif