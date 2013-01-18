#include "IBPlannerGraph.h"

#include "IBPlanner.h"
#include "CanvasBase.h"
#include "Graph\IBGBox.h"
#include "Graph\IBGFactBox.h"
#include "Graph\IBGActionBox.h"
#include "Action\IBAction.h"
#include "Fact\IBFactDef.h"

const uint	IBPlannerGraph::s_iMargin = 32;
const uint	IBPlannerGraph::s_iFactWidth = 80;
const uint	IBPlannerGraph::s_iFactTitleHeight = 18;
const uint	IBPlannerGraph::s_iFactVarHeight = 18;
const uint	IBPlannerGraph::s_iFactHeight = 36;
const uint	IBPlannerGraph::s_iFactMinSpace = 16;
const uint	IBPlannerGraph::s_iLinkWidth = 48;
const uint	IBPlannerGraph::s_iActionWidth = 128;
const uint	IBPlannerGraph::s_iActionMinHeight = 64;
const uint	IBPlannerGraph::s_iActionTitleHeight = 18;
const uint	IBPlannerGraph::s_iActionAnchorHeight = 20;
const uint	IBPlannerGraph::s_iActionVarHeight = 18;
const uint  IBPlannerGraph::s_iActionLinkSpace = 16;
      uint	IBPlannerGraph::s_iBoxWidth = 0;
      uint	IBPlannerGraph::s_iBoxMinHeight = 0;
const uint	IBPlannerGraph::s_iBoxSpace = 32;
const Color	IBPlannerGraph::s_oActionColor = Color(64, 192, 255);
const Color	IBPlannerGraph::s_oActionWorkColor = Color(192, 64, 128);
const Color	IBPlannerGraph::s_oFactColor = Color(128, 255, 128);
const Color	IBPlannerGraph::s_oFalseFactColor = Color(255, 64, 64);
const Color	IBPlannerGraph::s_oLinkColor = Color(128, 255, 255);
const Color	IBPlannerGraph::s_oBoxColor = Color(256, 128, 128);






IBPlannerGraph::IBPlannerGraph(const IBPlanner& oPlanner, CanvasBase& oGraphCanva)
	: IBPlannerDisplay(oPlanner)
	, m_oCanvas(oGraphCanva)
{
	IBPlannerGraph::s_iBoxWidth = IBPlannerGraph::s_iFactWidth + IBPlannerGraph::s_iLinkWidth + IBPlannerGraph::s_iActionWidth;
	IBPlannerGraph::s_iBoxMinHeight = IBPlannerGraph::s_iActionMinHeight;
}

IBPlannerGraph::~IBPlannerGraph()
{
	Destroy();
}

void IBPlannerGraph::Destroy()
{
	for (uint i=0 ; i<m_aBox.size() ; ++i)
		delete m_aBox[i];

	m_aBox.clear();
}

void IBPlannerGraph::Create(const IBPlanner& oPlanner)
{
	for (FactSet::const_iterator it = oPlanner.m_aGoals.begin() ; it != oPlanner.m_aGoals.end() ; ++it)
	{
		IBGBox* pGoalBox = new IBGBox(m_oCanvas, *it);
		m_aBox.push_back(pGoalBox);
	}
}

void IBPlannerGraph::Draw()
{
	int h = 0;
	for (uint i=0 ; i<m_aBox.size() ; ++i)
	{
		m_aBox[i]->Resize();
		h += m_aBox[i]->GetH();
	}

	int s = (m_oCanvas.GetHeight() - h) / (m_aBox.size() + 1);

	int y = s;
	for (uint i=0 ; i<m_aBox.size() ; ++i)
	{
		m_aBox[i]->SetX(m_oCanvas.GetWidth() - m_aBox[i]->GetW() - IBPlannerGraph::s_iMargin);
		m_aBox[i]->SetY(y);
		m_aBox[i]->Draw();
		y += m_aBox[i]->GetH() + s;
	}
}


void IBPlannerGraph::DrawGraph()
{
	m_oCanvas.CanvasBase::DrawRect(0, 0, m_oCanvas.GetWidth(), m_oCanvas.GetHeight(), Color(0, 255, 0));

	Destroy();

	Create(m_oPlanner);

	Draw();
}
