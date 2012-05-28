#ifndef __IBACTIONDEF_MOVECUBEFROMCUBETOTABLE_H__
#define __IBACTIONDEF_MOVECUBEFROMCUBETOTABLE_H__

#include "Utils.h"
#include "Action/IBActionDef.h"

class IBActionDef_MoveCubeFromCubeToTable : public IBActionDef
{
	public:
		IBActionDef_MoveCubeFromCubeToTable(const string& name, IBPlanner* pPlanner);
		virtual ~IBActionDef_MoveCubeFromCubeToTable();

		virtual void		Define();

	private:
};

#endif
