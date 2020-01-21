#ifndef __IBACTIONDEF_FOLLOWPATH_H__
#define __IBACTIONDEF_FOLLOWPATH_H__

#include "Utils.h"
#include "Action/IBActionDef.h"

class IBActionDef_FollowPath : public IBActionDef
{
	public:
		IBActionDef_FollowPath(const string& name, IBPlanner* pPlanner);
		virtual ~IBActionDef_FollowPath();

		virtual void			Define();
		
		virtual float		GetCost(const IBAction* pAction) const;

		virtual void			CreateOwnedVariables(IBAction* pAction) const override;
		virtual bool			Start(IBAction* pAction) const override;
		virtual bool			Execute(IBAction* pAction) const override;
		virtual bool			Abort(IBAction* pAction) const override;
		virtual bool			Finish(IBAction* pAction) const override;
		virtual void			Destroy(IBAction* pAction) const override;

	private:
};

#endif
