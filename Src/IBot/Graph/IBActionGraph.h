#ifndef __IBACTIONGRAPH_H__
#define __IBACTIONGRAPH_H__

#include "Utils.h"
//#include "Fact/IBFact.h"
//#include "Action/IBActionGraphDef.h"

class IBActionGraph
{
	public:
		IBActionGraph(IBAction* pAction);
		~IBActionGraph();

	public:
		void					Draw(CanvasBase& canva, int& x, int& y, const IBFact* pFact) const;

private:
		IBAction*			m_pAction;
};

#endif
