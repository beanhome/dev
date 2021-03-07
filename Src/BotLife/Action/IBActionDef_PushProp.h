#ifndef __IBACTIONDEF_PUSHPROP_H__
#define __IBACTIONDEF_PUSHPROP_H__

#include "Utils.h"
#include "Action/IBActionDef.h"

class IBActionDef_PushProp : public IBActionDef
{
	public:
		IBActionDef_PushProp(const string& name, IBPlanner* pPlanner);
		virtual ~IBActionDef_PushProp();

		virtual void			Define();
		
		virtual float			GetCost(const IBAction* pAction) const;

		virtual void			CreateOwnedVariables(IBAction* pAction) const override;
		virtual void			CompleteVariables(IBAction* pAction) const override;
		virtual bool			Start(IBAction* pAction) const override;
		virtual void			Destroy(IBAction* pAction) const override;

	private:
};

#endif
