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
		virtual float		Evaluate(const IBAction* pAction) const { return 1.f; }
		virtual bool		Execute(IBAction* pAction);

	private:
};

#endif
