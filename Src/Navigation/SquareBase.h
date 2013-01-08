#ifndef SQUAREBASE_H_
#define SQUAREBASE_H_

#include "Utils.h"
#include "GridBase.h"

class SquareBase
{
	public:
		SquareBase() {}

		virtual bool IsBlock() const = 0;

		class DistCondition
		{
			public :
				DistCondition(const GridOp& oGrid, Vector2 dest, int iDist)
					: m_oGrid(oGrid)
					, m_vDestination(dest)
					, m_iDistSq(iDist * iDist)
				{}

				bool Test(const Vector2& loc, const SquareBase& ) const
				{
					return (loc == m_vDestination || m_oGrid.DistanceSq(loc, m_vDestination) <= m_iDistSq);
				}

			private:

			
			private:
				const GridOp&	m_oGrid;
				Vector2			m_vDestination;
				int				m_iDistSq;
		};

	private:
};

#endif //SQUAREBASE_H_
