#ifndef __IBFACTDEF_OBJECTATPOS_H__
#define __IBFACTDEF_OBJECTATPOS_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_ObjectAtPos : public IBFactDef
{
	public:
		IBFactDef_ObjectAtPos(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_ObjectAtPos();

		virtual void			ResolveVariable(vector<IBObject*>& aUserData);

		virtual IBF_Result		Test(const vector<IBObject*>& aUserData);

		virtual void			Print(const vector<IBObject*>& aUserData, int tab) const;

	private:
};

class IBFactDef_HeavyObjectAtPos : public IBFactDef_ObjectAtPos
{
	public:
		IBFactDef_HeavyObjectAtPos(const string& name, IBPlanner* pPlanner);
		virtual IBF_Result		Test(const vector<IBObject*>& aUserData);
};


#endif
