#include "IBPlannerGraph.h"


#include "IBPlanner.h"
#include "CanvasBase.h"

#include "Fact\IBFact.h"
#include "Action\IBAction.h"
#include "Action\IBActionDef.h"
#include "World\IBCube.h"
#include "World\IBWorld.h"

extern IBWorld g_oWorld;

const uint	IBPlannerGraph::s_iMargin = 32;
const uint	IBPlannerGraph::s_iFactWidth = 64;
const uint	IBPlannerGraph::s_iFactTitleHeight = 18;
const uint	IBPlannerGraph::s_iFactVarHeight = 18;
const uint	IBPlannerGraph::s_iFactHeight = 36;
const uint	IBPlannerGraph::s_iFactMinSpace = 16;
const uint	IBPlannerGraph::s_iLinkWidth = 64;
const uint	IBPlannerGraph::s_iActionWidth = 172;
const uint	IBPlannerGraph::s_iActionMinHeight = 64;
const uint	IBPlannerGraph::s_iActionTitleHeight = 18;
const uint	IBPlannerGraph::s_iActionAnchorHeight = 20;
const uint	IBPlannerGraph::s_iActionVarHeight = 18;
      uint	IBPlannerGraph::s_iBoxWidth = 0;
      uint	IBPlannerGraph::s_iBoxMinHeight = 0;
const uint	IBPlannerGraph::s_iBoxSpace = 32;
const Color	IBPlannerGraph::s_oActionColor = Color(64, 192, 255);
const Color	IBPlannerGraph::s_oFactColor = Color(128, 255, 128);
const Color	IBPlannerGraph::s_oFalseFactColor = Color(255, 64, 64);
const Color	IBPlannerGraph::s_oLinkColor = Color(128, 255, 255);
const Color	IBPlannerGraph::s_oBoxColor = Color(256, 128, 128);


IBGBoxBase::IBGBoxBase()
	: m_pMainBox(NULL)
	, x(0), y(0)
	, w(0), h(0)
{

}

IBGBoxBase::IBGBoxBase(IBGBox* pMainBox)
	: m_pMainBox(pMainBox)
	, x(0), y(0)
	, w(0), h(0)
{

}

void IBGBoxBase::Draw(CanvasBase& canva, const Color& color) const
{
	canva.DrawRect(x, y, w, h, color);
}


IBGActionBox::IBGActionBox(IBGBox* pMainBox, IBAction* pAction)
	: IBGBoxBase(pMainBox)
	, m_pAction(pAction)
	, m_pPostCond(NULL)
{

}

void IBGActionBox::Draw(CanvasBase& canva) const
{
	IBGBoxBase::Draw(canva, IBPlannerGraph::s_oActionColor);

	canva.DrawLine(x, y+IBPlannerGraph::s_iActionTitleHeight, x+w-1, y+IBPlannerGraph::s_iActionTitleHeight, IBPlannerGraph::s_oActionColor);
	canva.Print(x+w/2, y+IBPlannerGraph::s_iActionTitleHeight/2, canva.GetPrintFont(), IBPlannerGraph::s_iActionTitleHeight-6, Center, IBPlannerGraph::s_oActionColor, "%s", m_pAction->GetDef()->GetName().c_str());

	int k=0;
	for (IBAction::VarMap::const_iterator it = m_pAction->GetVariables().begin() ; it != m_pAction->GetVariables().end() ; ++it, ++k)
	{
		const string& sName = m_pAction->GetDef()->GetVariables()[k];

		const IBCube* pCube = ((const IBCube*)it->second);
		canva.Print(x+w/2, y+IBPlannerGraph::s_iActionTitleHeight+IBPlannerGraph::s_iActionVarHeight/2 + IBPlannerGraph::s_iActionVarHeight*(k), canva.GetPrintFont(), IBPlannerGraph::s_iActionVarHeight-6, Center, IBPlannerGraph::s_oActionColor, "%s %s", sName.c_str(), pCube->GetName().c_str());
	}
}


IBGFactBox::IBGFactBox(IBGBox* pMainBox, IBFact* pFact)
	: IBGBoxBase(pMainBox)
	, m_pFact(pFact)
	, m_pCauseBox(NULL)
{
}

IBAction* IBGFactBox::GetCauseAction()
{
	return m_pFact->GetCauseAction();
}

void IBGFactBox::Draw(CanvasBase& canva) const
{
	Color oColor = (m_pFact->IsTrue() ? IBPlannerGraph::s_oFactColor : IBPlannerGraph::s_oFalseFactColor);

	IBGBoxBase::Draw(canva, oColor);

	canva.DrawLine(x, y+IBPlannerGraph::s_iFactTitleHeight, x+w-1, y+IBPlannerGraph::s_iFactTitleHeight, oColor);
	canva.Print(x+w/2, y+IBPlannerGraph::s_iFactTitleHeight/2, canva.GetPrintFont(), IBPlannerGraph::s_iFactTitleHeight-6, Center, IBPlannerGraph::s_oFactColor, "%s", m_pFact->GetFactDef()->GetName().c_str());

	for (uint i=0 ; i<m_pFact->GetVariables().size() ; ++i)
	{
		void* pVar = m_pFact->GetVariable(i);
		IBCube* pCube = (IBCube*)pVar;
		canva.Print(x+w/2, y+IBPlannerGraph::s_iFactTitleHeight + IBPlannerGraph::s_iFactVarHeight/2 + i*IBPlannerGraph::s_iFactVarHeight, canva.GetPrintFont(), IBPlannerGraph::s_iFactTitleHeight-6, Center, IBPlannerGraph::s_oFactColor, "%s", pCube->GetName().c_str());
	}
}


IBGBox::IBGBox()
	: m_pActionBox(NULL)
{
	//m_pActionBox = new IBGActionBox(this, NULL);
}

//IBGBox::IBGBox(IBGActionBox* pActionBox)
//	: m_pActionBox(pActionBox)
//{
//}

IBGBox::IBGBox(IBAction* pAction)
	: m_pActionBox(NULL)
{
	m_pActionBox = new IBGActionBox(this, pAction);

	for (uint i=0 ; i<pAction->GetPreCond().size() ; ++i)
	{
		AddFactCond(pAction->GetPreCond()[i]);
	}
}


IBGBox::~IBGBox()
{
	if (m_pActionBox != NULL)
		delete m_pActionBox;

	for (uint i=0 ; i<m_aFactBox.size() ; ++i)
	{
		delete m_aFactBox[i];
	}
}

/*
void IBGBox::SetAction(IBAction* pAction)
{
	if (pAction == NULL)
	{
		if (m_pActionBox != NULL)
		{
			delete m_pActionBox;
			m_pActionBox = NULL;
		}
	}
	else
	{
		if (m_pActionBox == NULL)
		{
			m_pActionBox = new IBGActionBox(this, pAction);
		}
		else
		{
			m_pActionBox->SetAction(pAction);
		}
	}
}
*/

void IBGBox::AddFactCond(IBFact* pFact)
{
	IBGFactBox* pFactBox = new IBGFactBox(this, pFact);
	m_aFactBox.push_back(pFactBox);

	if (pFact->GetCauseAction() != NULL)
	{
		IBGBox* pCauseBox = new IBGBox(pFact->GetCauseAction());
		m_aFactBox.back()->SetCauseBox(pCauseBox);
	}
}

void IBGBox::Draw(CanvasBase& canva) const
{
	IBGBoxBase::Draw(canva, IBPlannerGraph::s_oBoxColor);

	if (m_pActionBox != NULL)
		m_pActionBox->Draw(canva);

	int space = (m_pActionBox != NULL ? (m_pActionBox->GetH()-IBPlannerGraph::s_iActionTitleHeight)/(m_aFactBox.size()+1) : 0);

	for (uint i=0 ; i<m_aFactBox.size() ; ++i)
	{
		m_aFactBox[i]->Draw(canva);


		if (m_pActionBox != NULL)
		{
			canva.DrawLine(
					m_aFactBox[i]->GetX() + m_aFactBox[i]->GetW(),
					m_aFactBox[i]->GetY() + m_aFactBox[i]->GetH()/2,
					m_pActionBox->GetX(),
					m_pActionBox->GetY() + IBPlannerGraph::s_iActionTitleHeight + space*(i+1),
					IBPlannerGraph::s_oLinkColor);
		}

		if (m_aFactBox[i]->GetCauseAction() != NULL)
		{
			IBGActionBox* pPrevAction = m_aFactBox[i]->GetCauseBox()->GetActionBox();

			canva.DrawLine(
				m_aFactBox[i]->GetX(),
				m_aFactBox[i]->GetY() + m_aFactBox[i]->GetH()/2,
				pPrevAction->GetX() + pPrevAction->GetW(),
				pPrevAction->GetY() + pPrevAction->GetH()/2,
				IBPlannerGraph::s_oLinkColor);
		}
	}



}



IBPlannerGraph::IBPlannerGraph(const IBPlanner& oPlanner, CanvasBase& oWorldCanva, CanvasBase& oGraphCanva)
	: IBPlannerDisplay(oPlanner)
	, m_oWorldCanva(oWorldCanva)
	, m_oGraphCanva(oGraphCanva)
{
	IBPlannerGraph::s_iBoxWidth = IBPlannerGraph::s_iFactWidth + IBPlannerGraph::s_iLinkWidth + IBPlannerGraph::s_iActionWidth;
	IBPlannerGraph::s_iBoxMinHeight = IBPlannerGraph::s_iActionMinHeight;
}

IBPlannerGraph::~IBPlannerGraph()
{
}

void IBPlannerGraph::Init(const IBPlanner& oPlanner, CanvasBase& canva)
{
	IBGBox* pGoalBox =  new IBGBox();

	for (FactSet::const_iterator it = oPlanner.m_aGoals.begin() ; it != oPlanner.m_aGoals.end() ; ++it)
	{
		pGoalBox->AddFactCond(*it);
	}

	Insert(pGoalBox, 0);

	for (uint col = m_aBox.size()-1 ; col<m_aBox.size() ; --col)
	{
		for (uint row=0 ; row<m_aBox[col].size() ; ++row)
		{
			IBGBox* pBox = m_aBox[col][row];
			IBGBox* pTopBox = (row == 0 ? NULL : m_aBox[col][row-1]);

			pBox->SetX((m_aBox.size()-1-col) * (s_iBoxWidth + s_iLinkWidth) + s_iMargin);
			pBox->SetY((row == 0 ? 0 : pTopBox->GetY() + pTopBox->GetH()) + s_iMargin);
			pBox->SetW(pBox->GetActionBox() != NULL ? s_iBoxWidth : s_iFactWidth);
			//pBox->SetH(max(m_iBoxMinHeight, pBox->m_aCond.size() * (m_iFactHeight + m_iFactMinSpace)));

			pBox->SetH(0);
			for (uint i=0 ; i<pBox->GetFactBox().size() ; ++i)
			{
				IBFact* pFact = pBox->GetFactBox()[i]->GetFact();
				pBox->SetH(pBox->GetH() + s_iFactTitleHeight + (pFact->GetFactDef()->GetDegree() * s_iFactVarHeight) + s_iFactMinSpace);

				//pBox->GetFactBox()[i]->GetCauseBox();

			}

			/*
			for (uint i=0 ; i<pBox->m_aPrevBox.size() ; ++i)
			{
				if (pBox->y + pBox->h < pBox->m_aPrevBox[i]->y + pBox->m_aPrevBox[i]->h)
					pBox->h = max(pBox->h, pBox->m_aPrevBox[i]->y + pBox->m_aPrevBox[i]->h - pBox->y);
			}
			*/

			if (pBox->GetActionBox() != NULL)
			{
				pBox->GetActionBox()->SetX(pBox->GetX() + s_iFactWidth + s_iLinkWidth);
				pBox->GetActionBox()->SetW(s_iActionWidth);
				pBox->GetActionBox()->SetH(max(s_iActionMinHeight, s_iActionTitleHeight + pBox->GetFactBox().size() * s_iActionAnchorHeight));
				pBox->GetActionBox()->SetY(pBox->GetY() + (pBox->GetH()-pBox->GetActionBox()->GetH())/2);
			}

			uint space = pBox->GetH() / pBox->GetFactBox().size();
			for (uint i=0 ; i<pBox->GetFactBox().size() ; ++i)
			{
				IBGFactBox* pFactBox =  pBox->GetFactBox()[i];
				IBFact* pFact = pBox->GetFactBox()[i]->GetFact();
				pFactBox->SetX(pBox->GetX());
				pFactBox->SetW(s_iFactWidth);
				pFactBox->SetH(s_iFactTitleHeight + pFact->GetFactDef()->GetDegree() * s_iFactVarHeight);
				pFactBox->SetY(pBox->GetY() + space * i + (space-pFactBox->GetH()) / 2);
			}
		}
	}
}

#if 0
void IBPlannerGraph::AddBox(const IBPlanner& oPlanner, IBAction* pAction, Box* pParentBox, uint col)
{
	if (m_aColumn.size() <= col)
		m_aColumn.resize(col+1);

	Box* pBox = new Box;

	pBox->m_oActionBox.m_pAction = pAction;
	pBox->m_aCondBox.resize(pAction->m_aPreCond.size());

	m_aColumn[col].m_aBox.push_back(pBox);

	pParentBox->m_aPrevBox.push_back(pBox);

	for (uint i=0 ; i<pAction->m_aPreCond.size() ; ++i)
	{
		pBox->m_aCondBox[i].m_pFact = pAction->m_aPreCond[i];

		if (pAction->m_aPreCond[i]->GetCauseAction() != NULL)
		{
			AddBox(oPlanner, pAction->m_aPreCond[i]->GetCauseAction(), pBox, col+1);
		}
	}

}
#endif

void IBPlannerGraph::Insert(IBGBox* pBox, uint col)
{
	if (col >= m_aBox.size())
		m_aBox.resize(col+1);

	m_aBox[col].push_back(pBox);

	for (uint i=0 ; i<pBox->GetFactBox().size() ; ++i)
	{
		IBGFactBox* pFactBox = pBox->GetFactBox()[i];
		IBGBox* pPreBox = pFactBox->GetCauseBox();

		if (pPreBox != NULL)
			Insert(pPreBox, col+1);
	}
}

void IBPlannerGraph::DrawWorld()
{
	int size = 48;
	int space = 32;
	int line = size*3;
	int left_space = 32;

	m_oWorldCanva.DrawLine(left_space, line, left_space + (size*g_oWorld.GetCubes().size()) + ((size+1)*g_oWorld.GetCubes().size()), line, Color(192, 255, 255));

	for (uint i=0 ; i < g_oWorld.GetCubes().size() ; ++i)
	{
		IBCube* pCube = &g_oWorld.GetCubes()[i];

		if (g_oWorld.GetTable().HasCube(pCube))
		{
			DrawCube(pCube, m_oWorldCanva, i, 0);
		}
	}
}

void IBPlannerGraph::DrawCube(const IBCube* pCube, CanvasBase& canva, int i, int j)
{
	int size = 48;
	int space = 32;
	int line = size*3;
	int left_space = 32;

	canva.DrawRect(left_space + space + i*(size+space), line-(size*(j+1)), size, size, Color(255, 255, 255));
	canva.Print(left_space + space + i*(size+space) + size/2, line - (size*j) - size/2, canva.GetPrintFont(), 12, Center, Color(255, 255, 255), "%s", pCube->GetName().c_str());

	if (pCube->GetTopCube() != NULL)
	{
		DrawCube(pCube->GetTopCube(), canva, i, j+1);
	}
}

void IBPlannerGraph::DrawGraph()
{
	if (m_aBox.size() > 0)
	{
		for (uint row=0 ; row<m_aBox[0].size() ; ++row)
		{
			delete m_aBox[0][row];
		}
		m_aBox.clear();
	}

	Init(m_oPlanner, m_oGraphCanva);

	for (uint col = m_aBox.size()-1 ; col<m_aBox.size() ; --col)
	{
		for (uint row=0 ; row<m_aBox[col].size() ; ++row)
		{
			m_aBox[col][row]->Draw(m_oGraphCanva);
		}
	}

#if 0
	for (uint col = m_aColumn.size()-1 ; col<m_aColumn.size() ; --col)
	//for (uint col = 0 ; col<m_aColumn.size() ; ++col)
	{
		for (uint row=0 ; row<m_aColumn[col].m_aBox.size() ; ++row)
		{
			Box* pBox = m_aColumn[col].m_aBox[row];
			m_oGraphCanva.DrawRect(pBox->x, pBox->y, pBox->w, pBox->h, m_oBoxColor);

			if (pBox->m_oActionBox.m_pAction != NULL)
			{
				pBox->m_oActionBox.x = pBox->x + m_iFactWidth + m_iLinkWidth;
				pBox->m_oActionBox.w = m_iActionWidth;
				pBox->m_oActionBox.h = max(m_iActionMinHeight, m_iActionTitleHeight + pBox->m_aCondBox.size() * m_iActionAnchorHeight);
				pBox->m_oActionBox.y = pBox->y + (pBox->h-pBox->m_oActionBox.h)/2;
				m_oGraphCanva.DrawRect(pBox->m_oActionBox.x, pBox->m_oActionBox.y, pBox->m_oActionBox.w, pBox->m_oActionBox.h, m_oActionColor);
				m_oGraphCanva.DrawLine(pBox->m_oActionBox.x, pBox->m_oActionBox.y+m_iActionTitleHeight, pBox->m_oActionBox.x+pBox->m_oActionBox.w-1, pBox->m_oActionBox.y+m_iActionTitleHeight, m_oActionColor);
				m_oGraphCanva.Print(pBox->m_oActionBox.x+pBox->m_oActionBox.w/2, pBox->m_oActionBox.y+m_iActionTitleHeight/2, m_oGraphCanva.GetPrintFont(), m_iActionTitleHeight-6, Center, m_oActionColor, "%s", pBox->m_oActionBox.m_pAction->m_pDef->GetName().c_str());

				uint i=0;
				for (IBAction::VarMap::const_iterator it = pBox->m_oActionBox.m_pAction->GetVariables().begin() ; it != pBox->m_oActionBox.m_pAction->GetVariables().end() ; ++it, ++i)
				{
					//m_oGraphCanva.Print(pBox->m_oActionBox.x+pBox->m_oActionBox.w/2, pBox->m_oActionBox.y+m_iActionTitleHeight + i*m_iActionVarHeight + m_iActionVarHeight/2, m_oGraphCanva.GetPrintFont(), m_iActionVarHeight-6, Center, m_oActionColor, "%s 0x%x %s", it->first.c_str(), it->second, ( it->second != NULL ? ((IBCube*)it->second)->GetName().c_str() : "NULL" ));
					m_oGraphCanva.Print(pBox->m_oActionBox.x+pBox->m_oActionBox.w/2, pBox->m_oActionBox.y+m_iActionTitleHeight + i*m_iActionVarHeight + m_iActionVarHeight/2, m_oGraphCanva.GetPrintFont(), m_iActionVarHeight-6, Center, m_oActionColor, "%s %s", it->first.c_str(), ( it->second != NULL ? ((IBCube*)it->second)->GetName().c_str() : "NULL" ));
				}
			}

			uint space = pBox->h / pBox->m_aCondBox.size();

			for (uint i=0 ; i<pBox->m_aCondBox.size() ; ++i)
			{
				pBox->m_aCondBox[i].x = pBox->x;
				pBox->m_aCondBox[i].w = m_iFactWidth;
				pBox->m_aCondBox[i].h = m_iFactTitleHeight + pBox->m_aCondBox[i].m_pFact->GetFactDef()->GetDegree() * m_iFactVarHeight;
				pBox->m_aCondBox[i].y = pBox->y + space * i + (space-pBox->m_aCondBox[i].h) / 2;
				m_oGraphCanva.DrawRect(pBox->m_aCondBox[i].x, pBox->m_aCondBox[i].y, pBox->m_aCondBox[i].w, pBox->m_aCondBox[i].h, m_oFactColor);
				m_oGraphCanva.DrawLine(pBox->m_aCondBox[i].x, pBox->m_aCondBox[i].y+m_iFactTitleHeight, pBox->m_aCondBox[i].x+pBox->m_aCondBox[i].w-1, pBox->m_aCondBox[i].y+m_iFactTitleHeight, m_oFactColor);
				m_oGraphCanva.Print(pBox->m_aCondBox[i].x+pBox->m_aCondBox[i].w/2, pBox->m_aCondBox[i].y+m_iFactTitleHeight/2, m_oGraphCanva.GetPrintFont(), m_iFactTitleHeight-6, Center, m_oFactColor, "%s", pBox->m_aCondBox[i].m_pFact->GetFactDef()->GetName().c_str());

				if (pBox->m_oActionBox.m_pAction != NULL)
				{
					m_oGraphCanva.DrawLine(
						pBox->m_aCondBox[i].x + pBox->m_aCondBox[i].w, 
						pBox->m_aCondBox[i].y + pBox->m_aCondBox[i].h/2, 
						pBox->m_oActionBox.x, 
						//pBox->m_oActionBox.y + pBox->m_oActionBox.h/2,
						pBox->m_oActionBox.y + m_iActionTitleHeight + i*m_iActionAnchorHeight + m_iActionAnchorHeight/2,
						m_oLinkColor);
				}

				/*
				if (pBox->m_aPrevBox[i]->m_oActionBox.m_pAction != NULL)
				{
					m_oGraphCanva.DrawLine(
						pBox->m_aCondBox[i].x, 
						pBox->m_aCondBox[i].y + pBox->m_aCondBox[i].h/2, 
						pBox->m_aPrevBox[i]->m_oActionBox.x + pBox->m_aPrevBox[i]->m_oActionBox.w, 
						pBox->m_aPrevBox[i]->m_oActionBox.y + pBox->m_aPrevBox[i]->m_oActionBox.h/2,
						m_oLinkColor);
				}
				*/

				for (uint j=0 ; j<pBox->m_aCondBox[i].m_pFact->GetFactDef()->GetDegree() ; ++j)
				{
					void* var = pBox->m_aCondBox[i].m_pFact->GetVariable(j);
					m_oGraphCanva.Print(pBox->m_aCondBox[i].x+pBox->m_aCondBox[i].w/2, pBox->m_aCondBox[i].y+m_iFactTitleHeight + j*m_iFactVarHeight + m_iFactVarHeight/2, m_oGraphCanva.GetPrintFont(), m_iFactVarHeight-6, Center, m_oFactColor, "%s", ((IBCube*)var)->GetName().c_str());
				}
			}

			/*
			if (pBox->m_oActionBox.m_pAction != NULL)
			{
				m_oGraphCanva.DrawLine(
					pBox->m_oActionBox.x + , pBox->m_oActionBox.w
					pBox->m_oActionBox.y + pBox->m_oActionBox.h/2,
					pBox->m_oActionBox.m_pAction->
					m_oLinkColor);
			}
			*/

		}
	}
#endif
}
