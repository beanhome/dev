#ifndef __IBACTIONDEF_MOVECUBEFROMTABLETOCUBE_H__
#define __IBACTIONDEF_MOVECUBEFROMTABLETOCUBE_H__

#include "Utils.h"
#include "Action/IBActionDef.h"

class IBActionDef_MoveCubeFromTableToCube : public IBActionDef
{
	public:
		IBActionDef_MoveCubeFromTableToCube(const string& name, IBPlanner* pPlanner);
		virtual ~IBActionDef_MoveCubeFromTableToCube();

		virtual void		Define();
		virtual float		Evaluate(const IBAction* pAction) const { return 1.f; }
		virtual bool		Init(IBAction* pAction);
		virtual bool		Execute(IBAction* pAction);

	private:
};

#endif
