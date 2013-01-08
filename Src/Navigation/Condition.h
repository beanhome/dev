#ifndef CONDITION_H_
#define CONDITION_H_

#include "Utils.h"
#include "GridBase.h"

template <typename TCase>
class Condition
{
	public :
		Condition(Vector2 dest, int iDist)
			: m_vDestination(dest)
			, m_iDistSq(iDist * iDist)
		{}

		virtual bool Test(const GridBase<TCase>& oGrid, const Vector2& loc) const
		{
			return (loc == m_vDestination || oGrid.DistanceSq(loc, m_vDestination) <= m_iDistSq);
		}

	private:
		Vector2			m_vDestination;
		int				m_iDistSq;
};

#endif
