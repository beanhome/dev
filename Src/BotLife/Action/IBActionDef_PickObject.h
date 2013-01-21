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
		
		virtual bool			Init(IBAction* pAction);
		virtual bool			Start(IBAction* pAction);
		virtual bool			Execute(IBAction* pAction);
		virtual bool			Finish(IBAction* pAction);
		virtual void			Destroy(IBAction* pAction);

	private:
};

#endif
