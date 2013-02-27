#ifndef CONDITION_H_
#define CONDITION_H_

#include "Utils.h"
#include "GridBase.h"

template <typename TCase>
class Condition
{
	public :
		Condition()	{}
		virtual bool Test(const GridBase<TCase>& oGrid, const Vector2& loc) const  = 0;
};

template <typename TCase>
class Cond_Dist : public Condition<TCase>
{
	public :
		Cond_Dist(Vector2 dest, int iDist)
			: m_vDestination(dest)
			, m_iDist(iDist)
		{}

		virtual bool Test(const GridBase<TCase>& oGrid, const Vector2& loc) const
		{
			return (loc == m_vDestination || oGrid.Distance(loc, m_vDestination) <= m_iDist);
		}

	private:
		Vector2			m_vDestination;
		int				m_iDist;
};



#endif
