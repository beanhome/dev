#include "IBTreeNode.h"
#include "IBTreeFact.h"

#include "IBPlanner.h"
#include "GEngine.h"
#include "Canvas.h"
#include "Color.h"
#include "Utils.h"

Color FillColor = Color(0, 255, 255);
Color FrameColor = Color(0, 0, 255);

IBTreeNode::IBTreeNode(const class IBNode* pNode)
	: m_pNode(pNode)
{
	//Refresh();
	/*
	m_aLogFacts.reserve(m_pNode->GetFacts().size());

	for (FactSet::iterator it = m_pNode->GetFacts().begin(); it != m_pNode->GetFacts().end(); ++it)
	{
		IBFact* pFact = *it;
		m_aLogFacts.push_back(new IBTreeFact(pFact));
	}
	*/
}

IBTreeNode::~IBTreeNode()
{
	for (vector<IBTreeFact*>::iterator it = m_aLogFacts.begin(); it != m_aLogFacts.end(); ++it)
	{
		IBTreeFact* pFact = *it;
		delete pFact;
	}
}

void IBTreeNode::Refresh(Canvas& oCanvas)
{
	if (m_aLogFacts.size() != m_pNode->GetFacts().size())
	{
		ASSERT(m_aLogFacts.size() == 0);

		m_aLogFacts.reserve(m_pNode->GetFacts().size());

		for (FactSet::iterator it = m_pNode->GetFacts().begin(); it != m_pNode->GetFacts().end(); ++it)
		{
			IBFact* pFact = *it;
			m_aLogFacts.push_back(new IBTreeFact(pFact));
		}
	}

	for (vector<IBTreeFact*>::iterator it = m_aLogFacts.begin(); it != m_aLogFacts.end(); ++it)
	{
		IBTreeFact* pFact = *it;
		pFact->Refresh(oCanvas);
	}

	IBTreeBox::Refresh(oCanvas);
}

void IBTreeNode::Size(Canvas& oCanvas, sint32& w, sint32& h)
{
	w = 0;
	h = 0;

	for (vector<IBTreeFact*>::iterator it = m_aLogFacts.begin(); it != m_aLogFacts.end(); ++it)
	{
		IBTreeFact* pFact = *it;

		sint32 fw, fh;
		pFact->GetSize(fw, fh);

		w = std::max(w, fw);
		h += fh;
	}
}

void IBTreeNode::Draw(Canvas& oCanvas, sint32 x, sint32 y)
{
	sint32 Width;
	sint32 Height;

	GetSize(Width, Height);

	oCanvas.DrawFillRect(x, y, Width, Height, FillColor);
	oCanvas.DrawRect(x, y, Width, Height, FrameColor);

	for (vector<IBTreeFact*>::iterator it = m_aLogFacts.begin(); it != m_aLogFacts.end(); ++it)
	{
		IBTreeFact* pFact = *it;

		pFact->Draw(oCanvas, x, y);

		sint32 fw, fh;
		pFact->GetSize(fw, fh);
		oCanvas.DrawRect(x, y, fw, fh, FrameColor);

		y += fh;
	}
}
