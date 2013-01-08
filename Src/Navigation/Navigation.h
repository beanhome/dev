#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "Utils.h"
#include "Vector2.h"
#include "GridBase.h"
//#include "SquareBase.h"
#include "Condition.h"

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
		bool			FindPath(const Vector2& start, const Vector2& target, int iDist, Path& aPath);
		bool			FindPath(const Vector2& start, const Condition<TCase>& oCondition, Path& aPath);

		virtual bool	FindPath(const vector<Vector2>& start, const Condition<TCase>& oCondition, Path& aPath) = 0;


	protected:
		const Grid* m_pModelGrid;
};

template <typename TCase>
bool Navigation<TCase>::FindPath(const Vector2& start, const Vector2& target, Path& aPath)
{
	return FindPath(start, target, 0, aPath);
}

template <typename TCase>
bool Navigation<TCase>::FindPath(const Vector2& start, const Vector2& target, int iDist, Path& aPath)
{
	return FindPath(start, Cond_Dist<TCase>(target, iDist), aPath);
}

template <typename TCase>
bool Navigation<TCase>::FindPath(const Vector2& start, const Condition<TCase>& oCondition, Path& aPath)
{
	vector<Vector2> pos(1, start);
	return FindPath(pos, oCondition, aPath);
}




#endif
