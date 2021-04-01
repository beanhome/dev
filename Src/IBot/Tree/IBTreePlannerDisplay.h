#ifndef __IBTreePLANNERDISPLAY_H__
#define __IBTreePLANNERDISPLAY_H__

#include "Utils.h"
#include "Display/IBPlannerDisplay.h"
#include "Color.h"
#include "Canvas.h"

class CanvasBase;

class IBTreePlannerDisplay : public IBPlannerDisplay
{
	public:
		IBTreePlannerDisplay(Canvas& oGraphCanva, const class IBPlanner& oPlanner);
		virtual ~IBTreePlannerDisplay();

	public:
		virtual void				RefreshTree() override;
		virtual void				Update(float dt) override;
		virtual void				OnClick() override;
		virtual void				DrawGraph() override;

		bool						IsDraging() const { return m_bDraging; }
		void						StartDrag();
		void						UpdateDrag();
		void						StopDrag();

		const Canvas&			GetCanvas() const { return m_oCanvas; }
		//const class IBGPlanBox*	GetPlan() const { return m_pPlan; }

	private:
		void						ClampOrig(sint32& x, sint32& y);

	private:
		Canvas&					m_oCanvas;

		class IBTreeNode*		m_pStartNode;

		uint16					m_iMaxWidth;
		uint16					m_iMaxHeight;

		bool						m_bDraging;
		int						m_iStartDragX;
		int						m_iStartDragY;

	public:
		/*
		static const uint		s_iMargin;

		static const uint		s_iFactMinWidth;
		static const uint		s_iFactMinHeight;
		static const uint		s_iFactTitleHeight;
		static const uint		s_iFactTitleSize;
		static const uint		s_iFactEvalHeight;
		static const uint		s_iFactEvalSize;
		static const uint		s_iFactVarHeight;
		static const uint		s_iFactVarSpace;
		static const uint		s_iFactMinSpace;

		static const uint		s_iLinkWidth;

		static const uint		s_iActionMinWidth;
		static const uint		s_iActionMinHeight;
		static const uint		s_iActionTitleHeight;
		static const uint		s_iActionTitleSize;
		static const uint		s_iActionEvalHeight;
		static const uint		s_iActionEvalSize;
		static const uint		s_iActionVarHeight;
		static const uint		s_iActionVarSpace;
		static const uint		s_iActionLinkSpace;
		static const uint		s_iActionMinSpace;

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
		*/
};

#endif
