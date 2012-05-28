#ifndef __IBACTIONDEF_BOOLTOBOOL_H__
#define __IBACTIONDEF_BOOLTOBOOL_H__

#include "Utils.h"
#include "Action/IBActionDef.h"

class IBActionDef_BoolToBool : public IBActionDef
{
	public:
		IBActionDef_BoolToBool(const string& name, IBPlanner* pPlanner);
		virtual ~IBActionDef_BoolToBool();

		virtual void		Define();

	private:
};

#endif
