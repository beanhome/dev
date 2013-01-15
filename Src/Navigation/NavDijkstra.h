#ifndef NAVDIJKSTRA_H
#define NAVDIJKSTRA_H

#include "Utils.h"
#include "Vector2.h"
#include "Navigation.h"
#include "Path.h"
#include "Condition.h"


template <typename TCase>
class NavDijkstra : public Navigation<TCase>
{
	public:
		NavDijkstra(bool bDiagMode = false);
		NavDijkstra(const Grid& oGrid, bool bDiagMode = false);
		~NavDijkstra();

	public:
		struct Case
		{
			int iCount;
			uint iPreviousCase;
		};

		static const int BLOCK = -2;
		static const int BLANK = -1;
		static const int START = 0;

	public:
		virtual void						Create(const Grid& oGrid, bool bDiagMode = false);
								
		void								Init(const vector<Vector2>& start);
								
		bool								FindPath(const Vector2& start, const Condition<TCase>& oCondition, Path& aPath);
		bool								FindPath(const vector<Vector2>& start, const Condition<TCase>& oCondition, Path& aPath);
		Navigation<TCase>::State			FindPathStep(const vector<Vector2>& start, const Condition<TCase>& oCondition, Path& aPath);
								
		virtual void						FindPathInit(const Vector2& start, const Vector2& target, int iDist, Path& aPath);
		virtual Navigation<TCase>::State	FindPathStep(const Vector2& start, const Vector2& target, int iDist, Path& aPath);

		virtual bool						GetPath(const Vector2& vTarget, Path& oPath) const;
								
		const GridBase<Case>&				GetGrid() const { return m_oPathGrid; }
		const Case&							GetCase(const Vector2& coord) const { return m_oPathGrid.GetCase(coord); }
		void								PrintDebug() const;


	private:
		GridBase<Case>						m_oPathGrid;
		bool								m_bDiagMode;
								
		vector<uint>						m_aStep;
		uint								m_iHead;
		uint								m_iQueue;
};

template <typename TCase>
NavDijkstra<TCase>::NavDijkstra(bool bDiagMode)
	: Navigation()
	, m_bDiagMode(bDiagMode)
	, m_iHead(0)
	, m_iQueue(0)
{
}

template <typename TCase>
NavDijkstra<TCase>::NavDijkstra(const Grid& oGrid, bool bDiagMode)
	: Navigation(oGrid)
	, m_oPathGrid(oGrid.IsNormalized())
	, m_bDiagMode(bDiagMode)
	, m_iHead(0)
	, m_iQueue(0)
{
	m_aStep.resize(m_pModelGrid->GetWidth() * m_pModelGrid->GetHeight());
	m_oPathGrid.Init(m_pModelGrid->GetWidth(), m_pModelGrid->GetHeight());
}

template <typename TCase>
NavDijkstra<TCase>::~NavDijkstra()
{}

template <typename TCase>
void NavDijkstra<TCase>::Create(const Grid& oGrid, bool bDiagMode)
{
	Navigation::Create(oGrid);

	m_bDiagMode = bDiagMode;

	m_iHead = 0;
	m_iQueue = 0;

	m_aStep.resize(m_pModelGrid->GetWidth() * m_pModelGrid->GetHeight());
	m_oPathGrid.Init(m_pModelGrid->GetWidth(), m_pModelGrid->GetHeight());
}

template <typename TCase>
void NavDijkstra<TCase>::FindPathInit(const Vector2& start, const Vector2& target, int iDist, Path& aPath)
{
	vector<Vector2> pos(1, start);
	Init(pos);
}

template <typename TCase>
typename Navigation<TCase>::State NavDijkstra<TCase>::FindPathStep(const Vector2& start, const Vector2& target, int iDist, Path& aPath)
{
	vector<Vector2> pos(1, start);
	return FindPathStep(pos, Cond_Dist<TCase>(target, iDist), aPath);
}

template <typename TCase>
void NavDijkstra<TCase>::Init(const vector<Vector2>& start)
{
	// Initialisation
	for (uint id=0 ; id<m_oPathGrid.GetSize() ; ++id)
	{
		const TCase& square = m_pModelGrid->GetCase(id);
		bool bBlock = square.IsBlock();
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
	m_iQueue = (uint)start.size();
}

template <typename TCase>
typename Navigation<TCase>::State NavDijkstra<TCase>::FindPathStep(const vector<Vector2>& start, const Condition<TCase>& oCondition, Path& aPath)
{
	if (m_iHead >= m_aStep.size() || m_iHead >= m_iQueue)
		return FP_Fail;

	uint id = m_aStep[m_iHead];

	Case& oCase = m_oPathGrid.GetCase(id);
	Vector2 vCoord = m_oPathGrid.GetCoord(id);

	ASSERT(oCase.iCount != BLOCK);
	ASSERT(m_oPathGrid.GetIndex(vCoord) == id);

	int iMax = (m_bDiagMode ? EDirection_MAX : CardDirCount);
	int dir_offset = rand() % iMax;
	for (int dir = 0 ; dir < iMax ; ++dir)
	{
		Vector2 vSideCoord;
		if (m_oPathGrid.GetCoord(vCoord, (EDirection)((dir + dir_offset)%iMax), vSideCoord) == false)
			continue;

		Case& oSideCase = m_oPathGrid.GetCase(vSideCoord);
		if (oSideCase.iCount == BLANK)
		{
			oSideCase.iCount = oCase.iCount + 1;
			oSideCase.iPreviousCase = id;
			ASSERT(m_oPathGrid.DistanceSq(m_oPathGrid.GetCoord(id), vSideCoord) <= 2);
			uint iSideId = m_oPathGrid.GetIndex(vSideCoord);
			m_aStep[m_iQueue++] = iSideId;
		}

		if (oCondition.Test(*m_pModelGrid, vSideCoord))
		{
			GetPath(vSideCoord, aPath);
			return FP_Succeed;
		}
	}

	++m_iHead;

	return FP_Find;
}

template <typename TCase>
bool NavDijkstra<TCase>::FindPath(const Vector2& start, const Condition<TCase>& oCondition, Path& aPath)
{
	vector<Vector2> pos(1, start);
	return FindPath(pos, oCondition, aPath);
}

template <typename TCase>
bool NavDijkstra<TCase>::FindPath(const vector<Vector2>& start, const Condition<TCase>& oCondition, Path& aPath)
{
	Init(start);

	while (true)
	{
		switch (FindPathStep(start, oCondition, aPath))
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

template <typename TCase>
bool NavDijkstra<TCase>::GetPath(const Vector2& vTarget, Path& oPath) const
{
	oPath.Clear();

	const Case& oLastCase = m_oPathGrid.GetCase(vTarget);
	if (oLastCase.iCount < 0)
		return false;

	uint iLength = oLastCase.iCount;
	Vector2 pos = vTarget;

	for (uint i=0 ; i<iLength ; ++i)
	{
		oPath.PushFront(pos);

		const Case& oCase = m_oPathGrid.GetCase(pos);
		pos = m_oPathGrid.GetCoord(oCase.iPreviousCase);
	}

	oPath.PushFront(pos);

	return true;
}


#endif
