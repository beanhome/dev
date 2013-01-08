#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "Utils.h"
#include "Vector2.h"
#include "GridBase.h"
#include "SquareBase.h"

class Path;

template <typename TCase, typename TCond>
class Navigation
{
	public:
		typedef GridBase<TCase> Grid;
		//typedef typename TCase::TCond Cond;

	public:
		Navigation();
		Navigation(const Grid& oGrid) : m_pModelGrid(&oGrid) {}
		~Navigation() {}

		virtual void	Create(const Grid& oGrid) { m_pModelGrid = &oGrid; }

		//bool			FindPath(const Vector2& start, const Vector2& target, Path& aPath);
		//bool			FindPath(const Vector2& start, const Vector2& target, int iDist, Path& aPath);
		bool			FindPath(const Vector2& start, const TCond& oCondition, Path& aPath);

		virtual bool	FindPath(const vector<Vector2>& start, const TCond& oCondition, Path& aPath) = 0;


	protected:
		const Grid* m_pModelGrid;
};

/*
template <typename TCase, typename TCond>
bool Navigation<TCase, TCond>::FindPath(const Vector2& start, const Vector2& target, Path& aPath)
{
	return FindPath(start, target, 0, aPath);
}

template <typename TCase, typename TCond>
bool Navigation<SquareBase, SquareBase::DistCondition>::FindPath(const Vector2& start, const Vector2& target, int iDist, Path& aPath)
{
	return FindPath(start, SquareBase::DistCondition(*m_pModelGrid, target, iDist));
}
*/

template <typename TCase, typename TCond>
bool Navigation<TCase, TCond>::FindPath(const Vector2& start, const TCond& oCondition, Path& aPath)
{
	vector<Vector2> pos(1, start);
	return FindPath(pos, oCondition, aPath);
}




#endif
