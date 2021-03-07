#ifndef __IBACTIONDEF_MOVETO_H__
#define __IBACTIONDEF_MOVETO_H__

#include "Utils.h"
#include "Action/IBActionDef.h"

class IBActionDef_MoveTo : public IBActionDef
{
	public:
		IBActionDef_MoveTo(const string& name, IBPlanner* pPlanner);
		virtual ~IBActionDef_MoveTo();

		virtual void			Define();
		
		virtual float			GetCost(const IBAction* pAction) const;

		virtual void			CreateOwnedVariables(IBAction* pAction) const override;
		virtual void			PostCreated(IBAction* pAction) const override;
		virtual void			Update(IBAction* pAction) const override;
		virtual bool			Start(IBAction* pAction) const override;
		virtual void			Interrupt(IBAction* pAction) const override;
		virtual void			Destroy(IBAction* pAction) const override;

	private:
		static float			s_fFindPathStepDelay;
};

#endif
