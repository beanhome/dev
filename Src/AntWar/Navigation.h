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

		virtual bool FindPath(const Vector2& start, const Vector2& target, vector<Vector2>& aPath, int iTurn) = 0;

	protected:
		const Grid& m_oModelGrid;
};



#endif
