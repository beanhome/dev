#ifndef NAVASTAR_H
#define NAVASTAR_H

#include "Utils.h"
#include "Grid.h"
#include "Vector2.h"
#include "Navigation.h"


class NavAStar : public Navigation
{
	public:
		NavAStar(const Grid& oGrid);
		~NavAStar();

	public:
		typedef Vector2					CaseCoord;

		struct Case
		{
			int iCost;
			CaseCoord iPrevious;

			Case(int _iCost, CaseCoord _iPrev) : iCost(_iCost), iPrevious(_iPrev) {}
		};

		typedef map<CaseCoord, Case>	AStartMap;
		typedef pair<CaseCoord, Case>	AStartPair;

	public:
		virtual bool		FindPath(const Vector2& start, const Vector2& target, int iDist, Path& aPath, int iTurn);
		bool				GetPath(const Vector2& vTarget, Path& oPath) const;

	private:
		int					Cost(const Vector2& p1, const Vector2& p2) const;
		CaseCoord			GetCheaperOpenCase(const Vector2& target) const;


	private:

		AStartMap			m_aOpenList;
		AStartMap			m_aCloseList;
};



#endif
