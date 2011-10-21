#ifndef NAVDIJKSTRA_H
#define NAVDIJKSTRA_H

#include "Utils.h"
#include "Grid.h"
#include "Vector2.h"
#include "Navigation.h"
#include "Path.h"


class NavDijkstra : public Navigation
{
	public:
		NavDijkstra(bool bDiagMode = false);
		NavDijkstra(const Grid& oGrid, bool bDiagMode = false);
		~NavDijkstra();

	public:
		enum EType
		{
			None				= 0x0000,
			Undiscovered		= 0x0001,
			Unvisible			= 0x0002,
			Food				= 0x0004,
			EnemyHill			= 0x0008,
			EnemyAnt			= 0x0010,
			FriendHill			= 0x0020,
			FriendAnt			= 0x0040,
		};

		struct Case
		{
			int iCount;
			uint iPreviousCase;
		};

		static const int BLOCK = -2;
		static const int BLANK = -1;
		static const int START = 0;

	public:
		virtual void				Create(const Grid& oGrid, bool bDiagMode = false);

		void						Init(const Vector2& start, int iTurn);
		void						Init(const vector<Vector2>& start, int iTurn);

		virtual bool				FindPath(const Vector2& start, const Vector2& target, Path& aPath, int iTurn);
		int							FindNearest(const Vector2& start, int type, Path& aPath, int iTurn);
		bool						FindNearest(const Vector2& start, const vector<Vector2>& aTarget, Path& aPath, int iTurn);
		void						Explore(const vector<Vector2>& start, int iTurn) { Explore(start, vector<Vector2>(), iTurn); }
		void						Explore(const vector<Vector2>& start, const vector<Vector2>& target, int iTurn);
		void						Explore(const vector<Vector2>& start, int type, int iTurn);

		bool						GetPath(const Vector2& vTarget, Path& oPath) const;

		const GridBase<Case>&		GetGrid() const { return m_oPathGrid; }
		void						PrintDebug() const;


	private:
		GridBase<Case>				m_oPathGrid;
		bool						m_bDiagMode;

		vector<uint>				m_aStep;
		uint						m_iHead;
		uint						m_iQueue;
};



#endif
