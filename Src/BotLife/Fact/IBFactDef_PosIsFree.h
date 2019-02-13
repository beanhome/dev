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

		virtual IBF_Result		Test(const class IBFact* pFact) const override;
};


#endif
