#ifndef __IBPLANNERGRAPH_H__
#define __IBPLANNERGRAPH_H__

#include "Utils.h"
#include "Color.h"
#include "IBPlannerDisplay.h"
#include "Canvas.h"

class IBFact;
class IBAction;

class IBPlanner;
class CanvasBase;

class IBGBox;

class IBCube;


class IBPlannerGraph : public IBPlannerDisplay
{
	public:
		IBPlannerGraph(const IBPlanner& oPlanner, CanvasBase& oGraphCanva);
		virtual ~IBPlannerGraph();

	public:
		virtual void		DrawGraph();

	private:
		void				Destroy();
		void				Create(const IBPlanner& oPlanner);
		void				Draw();

	private:
		vector<IBGBox*>		m_aBox;
		Canvas				m_oCanvas;

	public:
		static const uint		s_iMargin;
		static const uint		s_iFactWidth;
		static const uint		s_iFactTitleHeight;
		static const uint		s_iFactVarHeight;
		static const uint		s_iFactHeight; // to del
		static const uint		s_iFactMinSpace; // to del
		static const uint		s_iLinkWidth;
		static const uint		s_iActionWidth;
		static const uint		s_iActionMinHeight;
		static const uint		s_iActionTitleHeight;
		static const uint		s_iActionAnchorHeight;
		static const uint		s_iActionVarHeight;
		static const uint		s_iActionLinkSpace;
		static       uint		s_iBoxWidth;
		static       uint		s_iBoxMinHeight;
		static const uint		s_iBoxSpace;

		static const Color		s_oActionColor;
		static const Color		s_oActionWorkColor;
		static const Color		s_oFactColor;
		static const Color		s_oFalseFactColor;
		static const Color		s_oLinkColor;
		static const Color		s_oBoxColor;

};

#endif
