#ifndef __IBACTIONDEF_DROPOBJECT_H__
#define __IBACTIONDEF_DROPOBJECT_H__

#include "Utils.h"
#include "Action/IBActionDef.h"

class IBActionDef_DropObject : public IBActionDef
{
	public:
		IBActionDef_DropObject(const string& name, IBPlanner* pPlanner);
		virtual ~IBActionDef_DropObject();

		virtual void			Define();

		virtual float			GetCost(const IBAction* pAction) const override;
		virtual void			CreateOwnedVariables(IBAction* pAction) const override;
		virtual void			CompleteVariables(IBAction* pAction) const override;
		virtual bool			Start(IBAction* pAction) const override;
		virtual void			Destroy(IBAction* pAction) const override;

	private:
};

#endif
