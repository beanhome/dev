#ifndef NAVASTAR_H
#define NAVASTAR_H

#include "Utils.h"
#include "Vector2.h"
#include "Navigation.h"
#include "Path.h"


template <typename TCase>
class NavAStar : public Navigation<TCase>
{
	public:
		typedef GridBase<TCase> Grid;

		NavAStar(const Grid& oGrid);
		virtual ~NavAStar();

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
		virtual void						FindPathInit(const Vector2& start, const Vector2& target, int iDist, Path& aPath);
		virtual typename Navigation<TCase>::State	FindPathStep(const Vector2& start, const Vector2& target, int iDist, Path& aPath);
		
		virtual bool						GetPath(const Vector2& vTarget, Path& oPath) const;

	private:
		int									Cost(const Vector2& p1, const Vector2& p2) const;
		CaseCoord							GetCheaperOpenCase(const Vector2& target) const;


	private:
								
		CaseCoord							m_oCurrentCoord;
		CaseCoord							m_oBestCoord;
		AStartMap							m_aOpenList;
		AStartMap							m_aCloseList;
};

template <typename TCase>
NavAStar<TCase>::NavAStar(const Grid& oGrid)
	: Navigation<TCase>(oGrid)
{
}

template <typename TCase>
NavAStar<TCase>::~NavAStar()
{}


template <typename TCase>
void NavAStar<TCase>::FindPathInit(const Vector2& start, const Vector2& target, int iDistSq, Path& aPath)
{
	m_aOpenList.clear();
	m_aCloseList.clear();

	int iStartCost = Cost(start, target);
	m_aCloseList.insert(AStartPair(start, Case(iStartCost, start)));

	m_oBestCoord = start;
	m_oCurrentCoord = start;
}

template <typename TCase>
typename Navigation<TCase>::State NavAStar<TCase>::FindPathStep(const Vector2& start, const Vector2& target, int iDist, Path& aPath)
{
	const Case& oCurrentCase = m_aCloseList.find(m_oCurrentCoord)->second;
	int iCurrentCost = oCurrentCase.iCost;
	int iToCaseCost = iCurrentCost - Cost(m_oCurrentCoord, target);

	EDirection offset = Navigation<TCase>::m_pModelGrid->GetDirection(m_oCurrentCoord, target);

	int iMax = (Navigation<TCase>::m_pModelGrid->IsDiagMode() ? EDirection_MAX : CardDirCount);
	int dir_offset = rand() % iMax;
	for (int dir = 0 ; dir < iMax ; ++dir)
	{
		Vector2 oSideCoord;
		if (Navigation<TCase>::m_pModelGrid->GetCoord(m_oCurrentCoord, (EDirection)((dir + dir_offset)%iMax), oSideCoord) == false)
			continue;

		int iCurDist = Navigation<TCase>::m_pModelGrid->Distance(oSideCoord, target);
		if (oSideCoord == target || (iCurDist <= iDist) && !Navigation<TCase>::m_pModelGrid->GetCase(oSideCoord).IsBlock())
		{
			m_aCloseList.insert(AStartPair(oSideCoord, Case(iToCaseCost + 1 + Cost(oSideCoord, target), m_oCurrentCoord)));
			GetPath(oSideCoord, aPath);
			return Navigation<TCase>::FP_Succeed;
		}

		if (Navigation<TCase>::m_pModelGrid->GetCase(oSideCoord).IsBlock())
			continue;

		if (m_aCloseList.find(oSideCoord) != m_aCloseList.end())
			continue;

		int iSideCost = iToCaseCost + 1 + Cost(oSideCoord, target);
		Case oCase(iSideCost, m_oCurrentCoord);

		typename AStartMap::iterator it = m_aOpenList.find(oSideCoord);
		if (it != m_aOpenList.end() && it->second.iCost > iSideCost)
		{
			it->second.iCost = iSideCost;
			it->second.iPrevious = m_oCurrentCoord;
		}
		else
		{
			m_aOpenList.insert(AStartPair(oSideCoord, Case(iSideCost, m_oCurrentCoord)));
		}
	}

	if (m_aOpenList.size() == 0)
	{
		GetPath(m_oBestCoord, aPath);
		return Navigation<TCase>::FP_Fail;
	}

	m_oCurrentCoord = GetCheaperOpenCase(target);
	typename AStartMap::iterator it = m_aOpenList.find(m_oCurrentCoord);
	m_aCloseList.insert(AStartPair(it->first, it->second));
	m_aOpenList.erase(it);

	if (Navigation<TCase>::m_pModelGrid->Distance(m_oBestCoord, target) > Navigation<TCase>::m_pModelGrid->Distance(m_oCurrentCoord, target))
		m_oBestCoord = m_oCurrentCoord;


	if (m_aCloseList.size() <= 0)
	{
		GetPath(m_oBestCoord, aPath);
		return Navigation<TCase>::FP_Fail;
	}

	return Navigation<TCase>::FP_Find;
}

template <typename TCase>
int NavAStar<TCase>::Cost(const Vector2& p1, const Vector2& p2) const
{
	int dx = abs(p1.x - p2.x);
	int dy = abs(p1.y - p2.y);

	if (dx > (int)Navigation<TCase>::m_pModelGrid->GetWidth() / 2)
		dx = (int)Navigation<TCase>::m_pModelGrid->GetWidth() - dx;

	if (dy > (int)Navigation<TCase>::m_pModelGrid->GetHeight() / 2)
		dy = (int)Navigation<TCase>::m_pModelGrid->GetHeight() - dy;

	return dx + dy;
}

template <typename TCase>
typename NavAStar<TCase>::CaseCoord NavAStar<TCase>::GetCheaperOpenCase(const Vector2& target) const
{
	typename AStartMap::const_iterator begin = m_aOpenList.begin();
	typename AStartMap::const_iterator end = m_aOpenList.end();
	typename AStartMap::const_iterator it;

	int iBestCost = -1;
	int iBestDist;
	CaseCoord iBestCase;
	for (it = begin ; it != end ; ++it)
	{
		const Case& oCase = it->second;

		if (iBestCost == -1 || oCase.iCost < iBestCost)
		{
			iBestCase = it->first;
			iBestCost = oCase.iCost;
			iBestDist = Navigation<TCase>::m_pModelGrid->Distance(iBestCase, target);
		}
		else if (oCase.iCost == iBestCost)
		{
			int iDist = Navigation<TCase>::m_pModelGrid->Distance(it->first, target);
			if (iDist < iBestDist)
			{
				iBestCase = it->first;
				iBestCost = oCase.iCost;
				iBestDist = iDist;
			}
		}
	}

	return iBestCase;
}

template <typename TCase>
bool NavAStar<TCase>::GetPath(const Vector2& vTarget, Path& oPath) const
{
	oPath.Clear();

	CaseCoord oCoord;
	CaseCoord oPreviousCoord = vTarget;
	do
	{
		oCoord = oPreviousCoord;
		oPreviousCoord = m_aCloseList.find(oCoord)->second.iPrevious;
		if (oPreviousCoord != oCoord)
			oPath.PushFront(oCoord);
	} while (oPreviousCoord != oCoord);

	oPath.PushFront(oPreviousCoord);

	return true;
}


#endif
