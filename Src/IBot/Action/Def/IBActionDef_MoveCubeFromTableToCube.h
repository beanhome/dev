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

	private:
};

#endif
