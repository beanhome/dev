#ifndef __IBACTIONDEF_MOVECUBEFROMCUBETOCUBE_H__
#define __IBACTIONDEF_MOVECUBEFROMCUBETOCUBE_H__

#include "Utils.h"
#include "Action/IBActionDef.h"

class IBActionDef_MoveCubeFromCubeToCube : public IBActionDef
{
	public:
		IBActionDef_MoveCubeFromCubeToCube(const string& name, IBPlanner* pPlanner);
		virtual ~IBActionDef_MoveCubeFromCubeToCube();

		virtual void		Define();
		virtual float		Evaluate(const IBAction* pAction) const { return 1.f; }
		virtual bool		Init(IBAction* pAction);
		virtual bool		Execute(IBAction* pAction);

private:
};

#endif
