#ifndef __IBACTIONDEF_FINDPATH_H__
#define __IBACTIONDEF_FINDPATH_H__

#include "Utils.h"
#include "Action/IBActionDef.h"

template<typename TCase>
class Navigation;
class BLSquare;

class IBActionDef_FindPath : public IBActionDef
{
	public:
		IBActionDef_FindPath(const string& name, IBPlanner* pPlanner);
		virtual ~IBActionDef_FindPath();

		virtual void			Define();

		virtual float			GetCost(const IBAction* pAction) const;

		virtual bool			Start(IBAction* pAction) const override;
		virtual void			Finish(IBAction* pAction, bool bInterrupted) const override;
		virtual void			Destroy(IBAction* pAction) const override;

	private:
		static float			s_fFindPathStepDelay;
};

#endif
