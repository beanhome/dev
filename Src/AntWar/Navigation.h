#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "Utils.h"
#include "Grid.h"
#include "Vector2.h"

class Path;

class Navigation
{
	public:
		Navigation();
		Navigation(const Grid& oGrid);
		~Navigation();

		virtual void Create(const Grid& oGrid);
		virtual bool FindPath(const Vector2& start, const Vector2& target, Path& aPath, int iTurn) = 0;

	protected:
		const Grid* m_pModelGrid;
};



#endif
