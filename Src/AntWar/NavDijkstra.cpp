#include "NavDijkstra.h"
#include "Square.h"
#include "World.h"
#include "Utils.h"
#include "StringUtils.h"

NavDijkstra::NavDijkstra(bool bDiagMode)
	: Navigation()
	, m_bDiagMode(bDiagMode)
	, m_iHead(0)
	, m_iQueue(0)
{
}

NavDijkstra::NavDijkstra(const Grid& oGrid, bool bDiagMode)
	: Navigation(oGrid)
	, m_bDiagMode(bDiagMode)
	, m_iHead(0)
	, m_iQueue(0)
{
	m_aStep.resize(m_pModelGrid->GetWidth() * m_pModelGrid->GetHeight());
	m_oPathGrid.Init(m_pModelGrid->GetWidth(), m_pModelGrid->GetHeight());
}

NavDijkstra::~NavDijkstra()
{}

void NavDijkstra::Create(const Grid& oGrid, bool bDiagMode)
{
	Navigation::Create(oGrid);

	m_bDiagMode = bDiagMode;

	m_iHead = 0;
	m_iQueue = 0;

	m_aStep.resize(m_pModelGrid->GetWidth() * m_pModelGrid->GetHeight());
	m_oPathGrid.Init(m_pModelGrid->GetWidth(), m_pModelGrid->GetHeight());
}

void NavDijkstra::Init(const Vector2& start, int iTurn)
{
	vector<Vector2> pos(1, start);
	Init(pos, iTurn);
}

void NavDijkstra::Init(const vector<Vector2>& start, int iTurn)
{
	// Initialisation
	for (uint id=0 ; id<m_oPathGrid.GetSize() ; ++id)
	{
		const Square& square = m_pModelGrid->GetCase(id);
		bool bBlock = square.IsBlock(iTurn);
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
}



bool NavDijkstra::FindPath(const Vector2& start, const Vector2& target, int iDistSq, Path& aPath, int iTurn)
{
	Init(start, iTurn);

	// Compute
	for (m_iHead = 0 ; m_iHead < m_aStep.size() && m_iHead < m_iQueue ; ++m_iHead)
	{
		uint id = m_aStep[m_iHead];

		Case& oCase = m_oPathGrid.GetCase(id);

		ASSERT(oCase.iCount != BLOCK);
		Vector2 vCoord = m_oPathGrid.GetCoord(id);
		ASSERT(m_oPathGrid.GetIndex(vCoord) == id);

		int dir_offset = rand() % CardDirCount;
		for (int dir = 0 ; dir < CardDirCount ; ++dir)
		{
			Vector2 vSideCoord = m_oPathGrid.GetCoord(vCoord, (EDirection)((dir + dir_offset)%CardDirCount));
			Case& oSideCase = m_oPathGrid.GetCase(vSideCoord);
			if (oSideCase.iCount == BLANK)
			{
				oSideCase.iCount = oCase.iCount + 1;
				oSideCase.iPreviousCase = id;
				ASSERT(m_oPathGrid.DistanceSq(m_oPathGrid.GetCoord(id), vSideCoord) == 1);
				uint iSideId = m_oPathGrid.GetIndex(vSideCoord);
				m_aStep[m_iQueue++] = iSideId;
			}

			int iCurDistSq = m_oPathGrid.DistanceSq(vSideCoord, target);
			if (vSideCoord == target || iCurDistSq <= iDistSq)
			{
				GetPath(vSideCoord, aPath);
				return true;
			}
		}
	}

	return false;
}


int NavDijkstra::FindNearest(const Vector2& start, int type, Path& aPath, int iTurn)
{
	Init(start, iTurn);

	// Browse
	for (m_iHead = 0 ; m_iHead < m_aStep.size() && m_iHead < m_iQueue ; ++m_iHead)
	{
		uint id = m_aStep[m_iHead];

		Case& oCase = m_oPathGrid.GetCase(id);

		ASSERT(oCase.iCount != BLOCK);
		Vector2 vCoord = m_oPathGrid.GetCoord(id);
		ASSERT(m_oPathGrid.GetIndex(vCoord) == id);

		int dir_offset = rand() % CardDirCount;
		for (int dir = 0 ; dir < CardDirCount ; ++dir)
		{
			Vector2 vSideCoord = m_oPathGrid.GetCoord(vCoord, (EDirection)((dir + dir_offset)%CardDirCount));
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
			if (!square.IsWater())
			{
				int sqtype = None;

				if (!square.IsDiscovered(iTurn))	sqtype |= Undiscovered;
				if (!square.IsVisible())			sqtype |= Unvisible;
				if (square.IsFood())				sqtype |= Food;
				if (square.IsEnemyHill())			sqtype |= EnemyHill;
				if (square.HasEnemyAnt())			sqtype |= EnemyAnt;
				if (square.IsFriendHill())			sqtype |= FriendHill;
				if (square.HasFriendAnt())			sqtype |= FriendAnt;
				if (square.GetAntInfluence() > 0)	sqtype |= Safe;

				if (type & sqtype)
				{
					GetPath((oSideCase.iCount == BLOCK ? vCoord : vSideCoord), aPath);
					ASSERT(aPath.GetLength() > 0);
					return sqtype;
				}
			}
		}
	}

	return None;
}

bool NavDijkstra::FindNearest(const Vector2& start, const vector<Vector2>& aTarget, Path& aPath, int iTurn)
{
	Init(start, iTurn);

	// Browse
	for (m_iHead = 0 ; m_iHead < m_aStep.size() && m_iHead < m_iQueue ; ++m_iHead)
	{
		uint id = m_aStep[m_iHead];

		Case& oCase = m_oPathGrid.GetCase(id);

		ASSERT(oCase.iCount != BLOCK);
		Vector2 vCoord = m_oPathGrid.GetCoord(id);
		ASSERT(m_oPathGrid.GetIndex(vCoord) == id);

		int dir_offset = rand() % CardDirCount;
		for (int dir = 0 ; dir < CardDirCount ; ++dir)
		{
			Vector2 vSideCoord = m_oPathGrid.GetCoord(vCoord, (EDirection)((dir + dir_offset)%CardDirCount));
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
					GetPath(vSideCoord, aPath);
					return true;
				}
			}
		}
	}

	return false;
}



void NavDijkstra::Explore(const vector<Vector2>& start, int type, int iMax, int iTurn)
{
	Init(start, iTurn);

	// Browse
	for (m_iHead = 0 ; m_iHead < m_aStep.size() && m_iHead < m_iQueue ; ++m_iHead)
	{
		uint id = m_aStep[m_iHead];

		Case& oCase = m_oPathGrid.GetCase(id);
		ASSERT(oCase.iCount != BLOCK);
		if (iMax > 0 && oCase.iCount == iMax)
			continue;

		Vector2 vCoord = m_oPathGrid.GetCoord(id);
		ASSERT(m_oPathGrid.GetIndex(vCoord) == id);

		int iMax = (m_bDiagMode ? EDirection_MAX : CardDirCount);
		int dir_offset = rand() % iMax;
		for (int dir = 0 ; dir < iMax ; ++dir)
		{
			Vector2 vSideCoord = m_oPathGrid.GetCoord(vCoord, (EDirection)((dir + dir_offset)%iMax));
			Case& oSideCase = m_oPathGrid.GetCase(vSideCoord);

			if (oSideCase.iCount == BLANK)
			{
				oSideCase.iCount = oCase.iCount + 1;
				oSideCase.iPreviousCase = id;

				int sqtype = None;

				const Square& square = m_pModelGrid->GetCase(vSideCoord);

				if (!square.IsDiscovered(iTurn))	sqtype |= Undiscovered;
				if (!square.IsVisible())			sqtype |= Unvisible;
				if (square.IsFood())				sqtype |= Food;
				if (square.IsEnemyHill())			sqtype |= EnemyHill;
				if (square.HasEnemyAnt())			sqtype |= EnemyAnt;
				if (square.IsFriendHill())			sqtype |= FriendHill;
				if (square.HasFriendAnt())			sqtype |= FriendAnt;
				if (square.GetAntInfluence() > 0)	sqtype |= Safe;

				if (! (type & sqtype))
				{
					uint iSideId = m_oPathGrid.GetIndex(vSideCoord);
					m_aStep[m_iQueue++] = iSideId;
				}
			}
		}
	}
}

void NavDijkstra::Explore(const vector<Vector2>& start, const vector<Vector2>& target, int iMax, int iTurn)
{
	Init(start, iTurn);

	// Browse
	for (m_iHead = 0 ; m_iHead < m_aStep.size() && m_iHead < m_iQueue ; ++m_iHead)
	{
		uint id = m_aStep[m_iHead];

		Case& oCase = m_oPathGrid.GetCase(id);

		ASSERT(oCase.iCount != BLOCK);
		if (iMax > 0 && oCase.iCount == iMax)
			continue;

		Vector2 vCoord = m_oPathGrid.GetCoord(id);
		ASSERT(m_oPathGrid.GetIndex(vCoord) == id);

		int iMax = (m_bDiagMode ? EDirection_MAX : CardDirCount);
		int dir_offset = rand() % iMax;
		for (int dir = 0 ; dir < iMax ; ++dir)
		{
			Vector2 vSideCoord = m_oPathGrid.GetCoord(vCoord, (EDirection)((dir + dir_offset)%iMax));
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
