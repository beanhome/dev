#include "IBTreeNode.h"
#include "IBTreeFact.h"

#include "IBPlanner.h"
#include "GEngine.h"
#include "Canvas.h"
#include "Color.h"
#include "Utils.h"
#include "IBTreeAction.h"
#include "IBTreeActionNode.h"
#include "IBTreeBox_Image.h"

Color FillColor = Color(0, 255, 255);
Color FrameColor = Color(0, 0, 255);
sint32 FactOffset = 12;
sint32 ActionOffset = 16;

IBTreeNode::IBTreeNode(Canvas& oCanvas, IBTreeBox* pParent, const class IBNode* pNode)
	: IBTreeBox(oCanvas, pParent)
	, m_pNode(pNode)
{
}

IBTreeNode::~IBTreeNode()
{
	for (IBTreeFact* pTreeFact : m_aTreeFacts)
	{
		delete pTreeFact;
	}
}

void IBTreeNode::RefreshTree()
{
	if (m_aTreeFacts.size() != m_pNode->GetFacts().size())
	{
		ASSERT(m_aTreeFacts.size() == 0);

		for (IBFact* pFact : m_pNode->GetFacts())
			m_aTreeFacts.push_back(new IBTreeFact(m_oCanvas, this, pFact));
	}

	for (IBTreeFact* pTreeFact : m_aTreeFacts)
	{
		pTreeFact->RefreshTree();
	}

	UpdateSize();
}

void IBTreeNode::SetPos(sint32 x, sint32 y)
{
	IBTreeBox::SetPos(x, y);
	UpdatePos();
}


void IBTreeNode::Update(float dt, sint32 iMouseX, sint32 iMouseY)
{
	IBTreeBox::Update(dt, iMouseX, iMouseY);

	for (IBTreeFact* pTreeFact : m_aTreeFacts)
	{
		pTreeFact->Update(dt, iMouseX, iMouseY);

		for (IBTreeActionNode* pTreeActionNode : pTreeFact->m_aTreeActionNodes)
		{
			pTreeActionNode->Update(dt, iMouseX, iMouseY);
		}
	}
}

void IBTreeNode::UpdatePos()
{
	sint32 y = m_iPosY;

	auto aFactList = m_aTreeFacts;

	sint32 i = 0;
	for (IBTreeFact* pTreeFact : aFactList)
	{
		pTreeFact->SetPos(m_iPosX + i * FactOffset, y);
		y += pTreeFact->GetHeight();
		++i;
	}

	y += 5;

	i = aFactList.size() - 1;
	aFactList.reverse();
	for (IBTreeFact* pTreeFact : aFactList)
	{
		if (pTreeFact->m_bFolded == false)
		{
			for (IBTreeActionNode* pTreeActionNode : pTreeFact->m_aTreeActionNodes)
			{
				pTreeActionNode->SetPos(m_iPosX + (i + 1) * ActionOffset, y);
				y += pTreeActionNode->GetHeight();
			}
		}
		--i;
	}
}

void IBTreeNode::ComputeSize()
{
	m_iWidth = 0;
	m_iHeight = 0;

	sint32 i = 0;
	for (IBTreeFact* pTreeFact : m_aTreeFacts)
	{
		sint32 fw, fh;
		pTreeFact->GetSize(fw, fh);

		m_iWidth = std::max(m_iWidth, fw + i * FactOffset);
		m_iHeight += fh;

		if (pTreeFact->m_bFolded == false)
		{
			for (IBTreeActionNode* pTreeActionNode : pTreeFact->m_aTreeActionNodes)
			{
				sint32 aw, ah;
				pTreeActionNode->GetSize(aw, ah);

				m_iWidth = std::max(m_iWidth, aw + (i + 1) * ActionOffset);
				m_iHeight += ah;
			}
		}
		++i;
	}

	m_iHeight += 5;
}

void IBTreeNode::OnMouseClick(sint32 iMouseX, sint32 iMouseY)
{
	for (IBTreeFact* pTreeFact : m_aTreeFacts)
	{
		pTreeFact->MouseClick(iMouseX, iMouseY);

		for (IBTreeActionNode* pTreeActionNode : pTreeFact->m_aTreeActionNodes)
		{
			pTreeActionNode->MouseClick(iMouseX, iMouseY);
		}
	}
}


void IBTreeNode::Draw() const
{
	sint32 iFactsWidth = 0;
	sint32 iFactsHeight = 0;

	sint32 i = 0;
	for (const IBTreeFact* pTreeFact : m_aTreeFacts)
	{
		sint32 w, h;
		pTreeFact->GetSize(w, h);
		iFactsWidth = max(iFactsWidth, w + i * FactOffset);
		iFactsHeight += h;
		++i;
	}

	m_oCanvas.DrawFillRect(m_iPosX, m_iPosY, iFactsWidth, iFactsHeight, FillColor);

	for (IBTreeFact* pTreeFact : m_aTreeFacts)
	{
		pTreeFact->Draw();

		if (pTreeFact->m_bFolded == false)
		{
			for (IBTreeActionNode* pTreeActionNode : pTreeFact->m_aTreeActionNodes)
			{
				pTreeActionNode->Draw();

				sint32 x1 = pTreeFact->m_pFoldArrow->GetPosX() + pTreeFact->m_pFoldArrow->GetWidth() / 2;
				sint32 y1 = pTreeFact->m_pFoldArrow->GetPosY() + pTreeFact->m_pFoldArrow->GetHeight();
				sint32 x2 = x1;
				sint32 y2 = pTreeActionNode->GetPosY() + pTreeActionNode->m_pTreeAction->m_pActionTitleFont->GetSize()/2;
				sint32 x3 = pTreeActionNode->GetPosX();
				sint32 y3 = y2;

				m_oCanvas.DrawLine(x1, y1, x2, y2, Color::White);
				m_oCanvas.DrawLine(x2, y2, x3, y3, Color::White);
			}
		}
	}

	m_oCanvas.DrawRect(m_iPosX, m_iPosY, iFactsWidth, iFactsHeight, FrameColor);
}
