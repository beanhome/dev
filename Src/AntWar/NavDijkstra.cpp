#include "NavDijkstra.h"
#include "Square.h"
#include "World.h"
#include "Utils.h"
#include "StringUtils.h"

NavDijkstra::NavDijkstra()
	: Navigation()
	, m_iHead(0)
	, m_iQueue(0)
{
}

NavDijkstra::NavDijkstra(const Grid& oGrid)
	: Navigation(oGrid)
	, m_iHead(0)
	, m_iQueue(0)
{
	m_aStep.resize(m_pModelGrid->GetWidth() * m_pModelGrid->GetHeight());
	m_oPathGrid.Init(m_pModelGrid->GetWidth(), m_pModelGrid->GetHeight());
}

NavDijkstra::~NavDijkstra()
{}

void NavDijkstra::Init(const Grid& oGrid)
{
	Navigation::Init(oGrid);

	m_iHead = 0;
	m_iQueue = 0;

	m_aStep.resize(m_pModelGrid->GetWidth() * m_pModelGrid->GetHeight());
	m_oPathGrid.Init(m_pModelGrid->GetWidth(), m_pModelGrid->GetHeight());
}


bool NavDijkstra::FindPath(const Vector2& start, const Vector2& target, vector<Vector2>& aPath, int iTurn)
{
	// Initialisation
	for (uint id=0 ; id<m_oPathGrid.GetSize() ; ++id)
	{
		const Square& square = m_pModelGrid->GetCase(id);
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


				return true;
			}
		}
	}

	return false;
}


int NavDijkstra::FindNearest(const Vector2& start, int type, vector<Vector2>& aPath, int iTurn)
{
	// Initialisation
	for (uint id=0 ; id<m_oPathGrid.GetSize() ; ++id)
	{
		const Square& square = m_pModelGrid->GetCase(id);
		bool bBlock = !square.IsDiscovered(iTurn) || square.IsWater();
		m_oPathGrid.GetCase(id).iCount = (bBlock ? BLOCK : BLANK);
		m_oPathGrid.GetCase(id).iPreviousCase = (uint)-1;
	}

	uint iStartId = m_oPathGrid.GetIndex(start.x, start.y);
	m_oPathGrid.GetCase(iStartId).iCount = START;

	m_aStep[0] = iStartId;
	m_iHead = 0;
	m_iQueue = 1;

	// Browse
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

			const Square& square = m_pModelGrid->GetCase(vSideCoord);

			int sqtype = None;

			if (!square.IsDiscovered(iTurn))	sqtype |= Undiscovered;
			if (!square.IsVisible())			sqtype |= Unvisible;
			if (square.IsFood())				sqtype |= Food;
			if (square.IsEnemyHill())			sqtype |= EnemyHill;
			if (square.HasEnemyAnt())			sqtype |= EnemyAnt;
			if (square.IsFriendHill())			sqtype |= FriendHill;
			if (square.HasFriendAnt())			sqtype |= FriendAnt;

			if (type & sqtype)
			{
				aPath.resize(oCase.iCount+1);
				aPath[aPath.size()-1] = vSideCoord;
				Vector2 pos = vCoord;
				for (uint k=aPath.size()-2 ; k<aPath.size() ; --k)
				{
					aPath[k] = pos;
					oCase = m_oPathGrid.GetCase(aPath[k]);
					pos = m_oPathGrid.GetCoord(oCase.iPreviousCase);
				}

				return sqtype;
			}
		}
	}

	return None;
}

bool NavDijkstra::FindNearest(const Vector2& start, const vector<Vector2>& aTarget, vector<Vector2>& aPath, int iTurn)
{
	// Initialisation
	for (uint id=0 ; id<m_oPathGrid.GetSize() ; ++id)
	{
		const Square& square = m_pModelGrid->GetCase(id);
		bool bBlock = !square.IsDiscovered(iTurn) || square.IsWater();
		m_oPathGrid.GetCase(id).iCount = (bBlock ? BLOCK : BLANK);
		m_oPathGrid.GetCase(id).iPreviousCase = (uint)-1;
	}

	uint iStartId = m_oPathGrid.GetIndex(start.x, start.y);
	m_oPathGrid.GetCase(iStartId).iCount = START;

	m_aStep[0] = iStartId;
	m_iHead = 0;
	m_iQueue = 1;

	// Browse
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

			for (uint i=0 ; i<aTarget.size() ; ++i)
			{
				if (vSideCoord == aTarget[i])
				{
					aPath.resize(oCase.iCount+1);
					aPath[aPath.size()-1] = vSideCoord;
					Vector2 pos = vCoord;
					for (uint k=aPath.size()-2 ; k<aPath.size() ; --k)
					{
						aPath[k] = pos;
						oCase = m_oPathGrid.GetCase(aPath[k]);
						pos = m_oPathGrid.GetCoord(oCase.iPreviousCase);
					}

					return true;
				}
			}
		}
	}

	return false;
}



void NavDijkstra::Explore(const vector<Vector2>& start, const vector<Vector2>& target, int iTurn)
{
	// Initialisation
	for (uint id=0 ; id<m_oPathGrid.GetSize() ; ++id)
	{
		const Square& square = m_pModelGrid->GetCase(id);
		bool bBlock = !square.IsDiscovered(iTurn) || square.IsWater();
		m_oPathGrid.GetCase(id).iCount = (bBlock ? BLOCK : BLANK);
		m_oPathGrid.GetCase(id).iPreviousCase = (uint)-1;
	}

	for (uint i=0 ; i<start.size() ; ++i)
	{
		uint iStartId = m_oPathGrid.GetIndex(start[i]);
		m_oPathGrid.GetCase(iStartId).iCount = START;
		m_aStep[i] = iStartId;
	}

	m_iHead = 0;
	m_iQueue = start.size();

	// Browse
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

				uint i = 0;
				for (i=0 ; i<target.size() ; ++i)
				{
					if (target[i] == vSideCoord)
						break;
				}

				if (i == target.size())
				{
					uint iSideId = m_oPathGrid.GetIndex(vSideCoord);
					m_aStep[m_iQueue++] = iSideId;
				}
			}
		}
	}
}

bool NavDijkstra::GetPath(const Vector2& vTarget, Path& oPath) const
{
	oPath.SetTarget(vTarget);

	const Case& oLastCase = m_oPathGrid.GetCase(vTarget);
	if (oLastCase.iCount < 0)
		return false;
	
	uint iLength = oLastCase.iCount;

	oPath.GetList().resize(iLength);
	Vector2 pos = vTarget;
	for (uint k=iLength-1 ; k<iLength; --k)
	{
		oPath.GetList()[k] = pos;
		const Case& oCase = m_oPathGrid.GetCase(oPath.GetList()[k]);

		pos = m_oPathGrid.GetCoord(oCase.iPreviousCase);
	}

	oPath.SetStart(pos);

	return true;
}


void NavDijkstra::PrintDebug() const
{
	for (uint j=0 ; j<m_oPathGrid.GetHeight() ; ++j)
	{
		string line;
		for (uint i=0 ; i<m_oPathGrid.GetWidth() ; ++i)
		{
			switch (m_oPathGrid[i][j].iCount)
			{
				case 0:		line += 'X'; break;
				case BLOCK: line += '*'; break;
				case BLANK: line += '.'; break;
				default: line += FormatString("%d", m_oPathGrid[i][j].iCount % 10);
			}
		}
		LOG("%s\n", line.c_str());
	}
	LOG("\n");
}
