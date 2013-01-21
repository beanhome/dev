#ifndef __IBACTIONDEF_UNBLOCKPROP_H__
#define __IBACTIONDEF_UNBLOCKPROP_H__

#include "Utils.h"
#include "Action/IBActionDef.h"

class IBActionDef_UnblockProp : public IBActionDef
{
	public:
		IBActionDef_UnblockProp(const string& name, IBPlanner* pPlanner);
		virtual ~IBActionDef_UnblockProp();

		virtual void			Define();
		
		virtual bool			Init(IBAction* pAction);
		virtual bool			Start(IBAction* pAction);
		virtual bool			Execute(IBAction* pAction);
		virtual bool			Finish(IBAction* pAction);
		virtual void			Destroy(IBAction* pAction);

	private:
};

#endif
