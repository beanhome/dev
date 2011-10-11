#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "Utils.h"
#include "Grid.h"
#include "Vector2.h"


class Navigation
{
	public:
		Navigation(const Grid& oGrid);
		~Navigation();

		bool FindPath(const Vector2& start, const Vector2& target, vector<Vector2>& aPath, int iTurn);

	private:
		const Grid& m_oModelGrid;

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
