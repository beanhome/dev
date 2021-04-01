#include "IBTreeActionNode.h"

#include "IBPlanner.h"
#include "GEngine.h"
#include "Canvas.h"
#include "Color.h"
#include "Utils.h"
#include "Fact/IBFactDef.h"
#include "Action/IBAction.h"
#include "Action/IBActionDef.h"
#include "IBTreeNode.h"
#include "IBTreeAction.h"

sint32 iPreNodeVertiOffset = 10;
sint32 iPreNodeLeftOffset = 15;

IBTreeActionNode::IBTreeActionNode(Canvas& oCanvas, IBTreeBox* pParent, const class IBAction* pAction)
	: IBTreeBox_Container(oCanvas, pParent)
	, m_pAction(pAction)
	, m_pTreeAction(nullptr)
	, m_pPreTreeNode(nullptr)
	, m_bFolded(false)
{
}

IBTreeActionNode::~IBTreeActionNode()
{
	/*
	if (m_pTreeAction != nullptr)
		delete m_pTreeAction;

	if (m_pPreTreeNode != nullptr)
		delete m_pPreTreeNode;
	*/
}

void IBTreeActionNode::RefreshTree()
{
	if (m_pAction != nullptr && m_pTreeAction == nullptr)
	{
		m_pTreeAction = new IBTreeAction(m_oCanvas, this, m_pAction);
		m_aChildren.push_back(m_pTreeAction);
	}

	if (m_pAction != nullptr && m_pAction->GetPreNode() != nullptr && m_pPreTreeNode == nullptr)
	{
		m_pPreTreeNode = new IBTreeNode(m_oCanvas, this, m_pAction->GetPreNode());
		m_aChildren.push_back(m_pPreTreeNode);
	}

	if (m_pTreeAction != nullptr)
		m_pTreeAction->RefreshTree();

	if (m_pPreTreeNode != nullptr)
		m_pPreTreeNode->RefreshTree();
}


void IBTreeActionNode::UpdatePos()
{
	sint32 iActionWidth = 0;
	sint32 iActionHeight = 0;

	if (m_pTreeAction != nullptr)
	{
		m_pTreeAction->GetSize(iActionWidth, iActionHeight);
		m_pTreeAction->SetPos(m_iPosX, m_iPosY);
	}

	if (m_pPreTreeNode != nullptr)
	{
		m_pPreTreeNode->SetPos(m_iPosX + iPreNodeLeftOffset, m_iPosY + iActionHeight + iPreNodeVertiOffset);
	}
}

void IBTreeActionNode::ComputeSize()
{
	sint32 iActionWidth = 0;
	sint32 iActionHeight = 0;

	if (m_pTreeAction != nullptr)
		m_pTreeAction->GetSize(iActionWidth, iActionHeight);

	sint32 iPreNodeWidth = 0;
	sint32 iPreNodeHeight = 0;

	if (m_pPreTreeNode != nullptr)
		m_pPreTreeNode->GetSize(iPreNodeWidth, iPreNodeHeight);

	m_iWidth = max(iActionWidth, iPreNodeWidth + iPreNodeLeftOffset);
	m_iHeight = iActionHeight + iPreNodeVertiOffset + iPreNodeHeight;
}

void IBTreeActionNode::OnMouseClick(sint32 iMouseX, sint32 iMouseY)
{
	if (m_pTreeAction != nullptr)
		m_pTreeAction->MouseClick(iMouseX, iMouseY);

	if (m_pPreTreeNode != nullptr)
		m_pPreTreeNode->MouseClick(iMouseX, iMouseY);
}


void IBTreeActionNode::Draw() const
{
	if (m_pTreeAction != nullptr && m_pPreTreeNode != nullptr)
	{
		sint32 x = m_pTreeAction->GetPosX() + 10;
		sint32 y = m_pTreeAction->GetPosY() + m_pTreeAction->GetHeight();

		m_oCanvas.DrawLine(x, y, x, m_pPreTreeNode->GetPosY() + 10, Color::White);
		m_oCanvas.DrawLine(x, m_pPreTreeNode->GetPosY() + 10, m_pPreTreeNode->GetPosX(), m_pPreTreeNode->GetPosY() + 10, Color::White);
	}

	IBTreeBox_Container::Draw();
}
