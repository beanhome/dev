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

		enum State
		{
			FP_Create,
			FP_Init,
			FP_Find,
			FP_Succeed,
			FP_Fail
		};

	public:
		Navigation() : m_eState(FP_Create) {}
		Navigation(const Grid& oGrid) : m_pModelGrid(&oGrid), m_eState(FP_Create) {}
		virtual ~Navigation() {}

		virtual void							Create(const Grid& oGrid) { m_pModelGrid = &oGrid; }

		bool									FindPath(const Vector2& start, const Vector2& target, Path& aPath);
		bool									FindPath(const Vector2& start, const Vector2& target, int iDist, Path& aPath);

		virtual void							FindPathInit(const Vector2& start, const Vector2& target, int iDist, Path& aPath) = 0;
		virtual void							FindPathStep(const Vector2& start, const Vector2& target, int iDist, Path& aPath) = 0;
		typename Navigation<TCase>::State	GetState() const { return m_eState; }

		virtual bool							GetPath(const Vector2& vTarget, Path& oPath) const = 0;

	protected:
		const Grid* m_pModelGrid;
		typename Navigation<TCase>::State	m_eState;
};

template <typename TCase>
bool Navigation<TCase>::FindPath(const Vector2& start, const Vector2& target, Path& aPath)
{
	return FindPath(start, target, 0, aPath);
}

template <typename TCase>
bool Navigation<TCase>::FindPath(const Vector2& start, const Vector2& target, int iDistSq, Path& aPath)
{
	FindPathInit(start, target, iDistSq, aPath);

	while (true)
	{
		switch (FindPathStep(start, target, iDistSq, aPath))
		{
			case FP_Succeed:
				return true;

			case FP_Fail:
				return false;

			default:
				break;
		}
	}

	return false;
}



#endif
