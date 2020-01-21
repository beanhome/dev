#ifndef __IBACTIONDEF_PICKOBJECT_H__
#define __IBACTIONDEF_PICKOBJECT_H__

#include "Utils.h"
#include "Action/IBActionDef.h"

class IBActionDef_PickObject : public IBActionDef
{
	public:
		IBActionDef_PickObject(const string& name, IBPlanner* pPlanner);
		virtual ~IBActionDef_PickObject();

		virtual void			Define();
		
		virtual float		GetCost(const IBAction* pAction) const override;
		virtual void			CreateOwnedVariables(IBAction* pAction) const override;
		virtual bool			Start(IBAction* pAction) const override;
		virtual bool			Execute(IBAction* pAction) const override;
		virtual bool			Finish(IBAction* pAction) const override;
		virtual void			Destroy(IBAction* pAction) const override;

	private:
};

#endif
