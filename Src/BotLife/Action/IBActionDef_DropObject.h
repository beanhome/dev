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

		virtual float			Evaluate(const IBAction* pAction) const;
		
		virtual bool			Init(IBAction* pAction);
		virtual bool			Start(IBAction* pAction);
		virtual bool			Execute(IBAction* pAction);
		virtual bool			Finish(IBAction* pAction);
		virtual void			Destroy(IBAction* pAction);

	private:
};

#endif
