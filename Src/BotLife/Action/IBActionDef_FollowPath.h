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
		
		virtual bool			Start(IBAction* pAction);
		virtual bool			Execute(IBAction* pAction);
		virtual bool			Finish(IBAction* pAction);

	private:
};

#endif
