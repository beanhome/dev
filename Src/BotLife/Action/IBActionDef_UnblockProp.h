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
		
		virtual float		GetCost(const IBAction* pAction) const override;
		virtual bool			Init(IBAction* pAction) const override;
		virtual bool			Start(IBAction* pAction) const override;
		virtual bool			Execute(IBAction* pAction) const override;
		virtual bool			Finish(IBAction* pAction) const override;
		virtual void			Destroy(IBAction* pAction) const override;

	private:
};

#endif
