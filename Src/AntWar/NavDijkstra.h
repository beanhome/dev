#ifndef NAVDIJKSTRA_H
#define NAVDIJKSTRA_H

#include "Utils.h"
#include "Grid.h"
#include "Vector2.h"
#include "Navigation.h"


class NavDijkstra : public Navigation
{
	public:
		NavDijkstra(const Grid& oGrid);
		~NavDijkstra();

		virtual bool FindPath(const Vector2& start, const Vector2& target, vector<Vector2>& aPath, int iTurn);

	private:
		struct Case
		{
			int iCount;
			uint iPreviousCase;
		};
		GridBase<Case> m_oPathGrid;

		vector<uint> m_aStep;
		uint m_iHead, m_iQueue;
};



#endif
