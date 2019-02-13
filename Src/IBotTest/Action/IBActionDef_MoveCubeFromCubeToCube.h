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
		virtual void		CompleteVariables(IBAction* pAction) const;
		virtual float	GetCost(const IBAction* pAction) const { return 1.f; }
		virtual bool		Init(IBAction* pAction) const override;
		virtual bool		Execute(IBAction* pAction) const override;

private:
};

#endif
