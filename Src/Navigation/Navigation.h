#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "Utils.h"
#include "Vector2.h"
#include "GridBase.h"

class Path;

template <typename TCase>
class Navigation
{
	public:
		typedef GridBase<TCase> Grid;

	public:
		Navigation();
		Navigation(const Grid& oGrid) : m_pModelGrid(&oGrid) {}
		~Navigation() {}

		virtual void	Create(const Grid& oGrid) { m_pModelGrid = &oGrid; }

		bool			FindPath(const Vector2& start, const Vector2& target, Path& aPath);
		virtual bool	FindPath(const Vector2& start, const Vector2& target, int iDist, Path& aPath) = 0;

		virtual bool	GetPath(const Vector2& vTarget, Path& oPath) const = 0;


	protected:
		const Grid* m_pModelGrid;
};

template <typename TCase>
bool Navigation<TCase>::FindPath(const Vector2& start, const Vector2& target, Path& aPath)
{
	return FindPath(start, target, 0, aPath);
}





#endif
