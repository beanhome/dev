#include "Navigation.h"
#include "Square.h"
#include "World.h"
#include "StringUtils.h"

Navigation::Navigation(const Grid& oGrid)
: m_oModelGrid(oGrid)
, m_iHead(0)
, m_iQueue(0)
{
	m_aStep.resize(m_oModelGrid.GetWidth() * m_oModelGrid.GetHeight());
	m_oPathGrid.Init(m_oModelGrid.GetWidth(), m_oModelGrid.GetHeight());
}

Navigation::~Navigation()
{}

bool Navigation::FindPath(const Vector2& start, const Vector2& target, vector<Vector2>& aPath, int iTurn)
{
	const int BLOCK = -2;
	const int BLANK = -1;
	const int START = 0;

	// Initialisation

	for (uint id=0 ; id<m_oPathGrid.GetSize() ; ++id)
	{
		const Square& square = m_oModelGrid.GetCase(id);
		bool bBlock = !square.IsDiscovered(iTurn) || square.IsWater();
		m_oPathGrid.GetCase(id).iCount = (bBlock ? BLOCK : BLANK);
		m_oPathGrid.GetCase(id).iPreviousCase = (uint)-1;
	}

	uint iStartId = m_oPathGrid.GetIndex(start.x, start.y);
	m_oPathGrid.GetCase(iStartId).iCount = START;

	m_aStep[0] = iStartId;
	m_iHead = 0;
	m_iQueue = 1;

	// Compute
	for (m_iHead = 0 ; m_iHead < m_aStep.size() && m_iHead < m_iQueue ; ++m_iHead)
	{
		uint id = m_aStep[m_iHead];

		Case& oCase = m_oPathGrid.GetCase(id);

		ASSERT(oCase.iCount != BLOCK);

		for (int dir = 0 ; dir < EDirection_MAX ; ++dir)
		{
			Vector2 vCoord = m_oPathGrid.GetCoord(id);
			ASSERT(m_oPathGrid.GetIndex(vCoord) == id);
			Vector2 vSideCoord = m_oPathGrid.GetCoord(vCoord, (EDirection)dir);
			Case& oSideCase = m_oPathGrid.GetCase(vSideCoord);
			if (oSideCase.iCount == BLANK)
			{
				oSideCase.iCount = oCase.iCount + 1;
				oSideCase.iPreviousCase = id;
				ASSERT(m_oPathGrid.DistanceSq(m_oPathGrid.GetCoord(id), vSideCoord) == 1);
				uint iSideId = m_oPathGrid.GetIndex(vSideCoord);
				m_aStep[m_iQueue++] = iSideId;
			}

			if (vSideCoord == target)
			{
				aPath.resize(oCase.iCount+1);
				Vector2 pos = vSideCoord;
				for (uint k=aPath.size()-1 ; k<aPath.size() ; --k)
				{
					aPath[k] = pos;
					pos = m_oPathGrid.GetCoord(m_oPathGrid.GetCase(aPath[k]).iPreviousCase);
				}

				/*
				LOG("%d %d -> %d %d\n", start.x, start.y, target.x, target.y);

				for (uint j=0 ; j<m_oPathGrid.GetHeight() ; ++j)
				{
					string line;
					for (uint i=0 ; i<m_oPathGrid.GetWidth() ; ++i)
					{
						if (Vector2(i, j) == start)
						{
							line += 'O';
						}
						else if (Vector2(i, j) == target)
						{
							line += 'X';
						}
						else
						{
							switch (m_oPathGrid[i][j].iCount)
							{
								case BLOCK: line += '*'; break;
								case BLANK: line += '.'; break;
								default: line += FormatString("%d", m_oPathGrid[i][j].iCount % 10);
							}
						}
					}
					LOG("%s\n", line.c_str());
				}
				LOG("\n");
				*/


				return true;
			}
		}
	}

	return false;
}
