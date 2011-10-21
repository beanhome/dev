#include "NavAStar.h"
#include "Square.h"
#include "World.h"
#include "StringUtils.h"

NavAStar::NavAStar(const Grid& oGrid)
	: Navigation(oGrid)
{
}

NavAStar::~NavAStar()
{}

bool NavAStar::FindPath(const Vector2& start, const Vector2& target, Path& aPath, int iTurn)
{
	const int BLOCK = -2;
	const int BLANK = -1;
	const int START = 0;

	// init
	m_aOpenList.clear();
	m_aCloseList.clear();

	int iStartCost = Cost(start, target);
	m_aCloseList.insert(AStartPair(start, Case(iStartCost, start)));

	CaseCoord oCurrentCoord = start;

	do 
	{
		const Case& oCurrentCase = m_aCloseList.find(oCurrentCoord)->second;
		int iCurrentCost = oCurrentCase.iCost;
		int iToCaseCost = iCurrentCost - Cost(oCurrentCoord, target);

		for (int i=0 ; i<CardDirCount ; ++i)
		{
			CaseCoord oSideCoord = m_pModelGrid->GetCoord(oCurrentCoord, (EDirection)i);
			if (oSideCoord == target)
			{
				aPath.SetStart(start);
				aPath.SetTarget(target);

				vector<Vector2> aInvPath;
				CaseCoord oCoord;
				CaseCoord oPreviousCoord = oCurrentCoord;
				aInvPath.push_back(target);
				do
				{
					oCoord = oPreviousCoord;
					if (oCoord != start)
						aInvPath.push_back(oCoord);
					oPreviousCoord = m_aCloseList.find(oCoord)->second.iPrevious;
				} while (oPreviousCoord != oCoord);

				aPath.GetList().resize(aInvPath.size());
				for (uint i=0 ; i<aPath.GetList().size() ; ++i)
				{
					aPath.GetList()[i] = aInvPath[aPath.GetList().size()-1-i];
				}

				return true;
			}

			if (m_pModelGrid->GetCase(oSideCoord).IsBlock(iTurn, iToCaseCost))
				continue;

			if (m_aCloseList.find(oSideCoord) != m_aCloseList.end())
				continue;

			int iSideCost = iToCaseCost + 1 + Cost(oSideCoord, target);
			Case oCase(iSideCost, oCurrentCoord);

			AStartMap::iterator it = m_aOpenList.find(oSideCoord);
			if (it != m_aOpenList.end() && it->second.iCost > iSideCost)
			{
				it->second.iCost = iSideCost;
				it->second.iPrevious = oCurrentCoord;
			}
			else
			{
				m_aOpenList.insert(AStartPair(oSideCoord, Case(iSideCost, oCurrentCoord)));
			}
		}

		if (m_aOpenList.size() == 0)
			break;

		oCurrentCoord = GetCheaperOpenCase();
		AStartMap::iterator it = m_aOpenList.find(oCurrentCoord);
		m_aCloseList.insert(AStartPair(it->first, it->second));
		m_aOpenList.erase(it);

	} while (m_aCloseList.size() > 0);

	return false;
}

int NavAStar::Cost(const Vector2& p1, const Vector2& p2) const
{
	int dx = abs(p1.x - p2.x);
	int dy = abs(p1.y - p2.y);

	if (dx > (int)m_pModelGrid->GetWidth() / 2)
		dx = (int)m_pModelGrid->GetWidth() - dx;

	if (dy > (int)m_pModelGrid->GetHeight() / 2)
		dy = (int)m_pModelGrid->GetHeight() - dy;

	return dx + dy;
}

NavAStar::CaseCoord NavAStar::GetCheaperOpenCase() const
{
	AStartMap::const_iterator begin = m_aOpenList.begin();
	AStartMap::const_iterator end = m_aOpenList.end();
	AStartMap::const_iterator it;

	int iBestCost = -1;
	CaseCoord iBestCase;
	for (it = begin ; it != end ; ++it)
	{
		const Case& oCase = it->second;

		if (iBestCost == -1 || oCase.iCost < iBestCost)
		{
			iBestCase = it->first;
			iBestCost = oCase.iCost;
		}
	}

	return iBestCase;
}
