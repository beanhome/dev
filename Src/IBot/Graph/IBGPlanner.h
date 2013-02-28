#ifndef __IBGPlanner_H__
#define __IBGPlanner_H__

#include "Utils.h"
#include "IBPlanner.h"
#include "Color.h"
#include "Canvas.h"

class CanvasBase;

class IBGPlanner : public IBPlanner
{
	public:
		IBGPlanner(void* pOwner, CanvasBase& oGraphCanva);
		virtual ~IBGPlanner();

	public:
		virtual IBAction*		InstanciateAction(IBActionDef* pDef, IBFact* pPostCond1);
		virtual IBFact*			InstanciateFact(IBFactDef* pDef, const vector<IBObject*>& aUserData, IBAction* pEffectAction);

		void					Draw();

	private:
		Canvas					m_oCanvas;

	public:
		static const uint		s_iMargin;
		static const uint		s_iFactWidth;
		static const uint		s_iFactTitleHeight;
		static const uint		s_iFactVarHeight;
		static const uint		s_iFactVarSpace;
		static const uint		s_iFactHeight; // to del
		static const uint		s_iFactMinSpace; // to del
		static const uint		s_iLinkWidth;
		static const uint		s_iActionWidth;
		static const uint		s_iActionMinHeight;
		static const uint		s_iActionTitleHeight;
		static const uint		s_iActionAnchorHeight;
		static const uint		s_iActionVarHeight;
		static const uint		s_iActionVarSpace;
		static const uint		s_iActionLinkSpace;
		static       uint		s_iBoxWidth;
		static       uint		s_iBoxMinHeight;
		static const uint		s_iBoxSpace;

		static const Color		s_oActionColor;
		static const Color		s_oActionWorkColor;
		static const Color		s_oMarkToDelActionColor;
		static const Color		s_oReadyToDelActionColor;
		static const Color		s_oFactColor;
		static const Color		s_oFalseFactColor;
		static const Color		s_oMarkToDelFactColor;
		static const Color		s_oReadyToDelFactColor;
		static const Color		s_oLinkColor;
		static const Color		s_oBoxColor;
};

#endif
