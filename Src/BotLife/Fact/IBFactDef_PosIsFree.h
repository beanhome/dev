#ifndef __IBFACTDEF_POSISFREE_H__
#define __IBFACTDEF_POSISFREE_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"
#include "Map/BLSquare.h"
#include "Condition.h"

template<typename T>
class NavDijkstra;

class IBFactDef_PosIsFree : public IBFactDef
{
	public:
		IBFactDef_PosIsFree(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_PosIsFree();

		virtual void			ResolveVariable(vector<IBObject*>& aUserData);

		virtual IBF_Result		Test(const vector<IBObject*>& aUserData);

		virtual void			Print(const vector<IBObject*>& aUserData, int tab) const;

	private:
		NavDijkstra<BLSquare>* pNav;
};

class Cond_Free : public Condition<BLSquare>
{
	public :
		virtual bool Test(const GridBase<BLSquare>& oGrid, const Vector2& loc) const
		{
			return (oGrid.GetCase(loc).IsFree());
		}
};


#endif
