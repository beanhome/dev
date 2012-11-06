#include "IBActionGraph.h"

#include "CanvasBase.h"

IBActionGraph::IBActionGraph(IBAction* pAction)
	: m_pAction(pAction)
{
}

IBActionGraph::~IBActionGraph()
{

}



void IBActionGraph::Draw(CanvasBase& canva, int& x, int& y, const IBFact* pFact) const
{
	Color color(256, 256, 128);

	uint i=0;

	for (i=0 ; i<m_aPostCond.size() ; ++i)
		if (m_aPostCond[i] == pFact)
			break;

	assert(i < m_aPostCond.size());

	int max_in = max(m_aPreCond.size(), m_aPostCond.size());

	int title = 18;
	int offset = 22;
	int w = 256;
	int h = title + max_in * offset;
	int offset_left = (h - title)/m_aPreCond.size();
	int offset_right = (h - title)/m_aPostCond.size();
	int space = 64;
	int sq_size = 10;
	int title_space = 3;

	canva.DrawLine(x, y, x-space+sq_size, y, Color(255, 255, 255));

	x -= space + w/2;
	int top = y - (title + i*offset_right + offset_right/2);
	y = top + h/2;
	top += title;

	canva.DrawRect(x-w/2, y-h/2, w, h, color);
	canva.DrawLine(x-w/2, y-h/2+title, x+w/2-1, y-h/2+title, color);

	canva.Print(x, top-title/2, canva.GetPrintFont(), title-title_space*2, Center, color, "%s", m_pDef->GetName().c_str());

	int left = x-w/2;
	int right = x+w/2;

	for (uint j=0 ; j<m_aPreCond.size() ; ++j)
	{
		x = left - sq_size;
		y = top+j*offset_left+offset_left/2;

		canva.DrawRect(x, y-sq_size/2, sq_size, sq_size, color);
		m_aPreCond[j]->Draw(canva, x, y);
	}

	for (uint j=0 ; j<m_aPostCond.size() ; ++j)
		canva.DrawRect(right, top+j*offset_right+offset_right/2-sq_size/2, sq_size, sq_size, color);
}


