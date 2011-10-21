#ifndef HILL_H_
#define HILL_H_

#include "Utils.h"
#include "Vector2.h"
#include "NavDijkstra.h"

class Grid;

class Hill
{
	public:
		Hill(const Vector2& loc, int iPlayer, const Grid& oGrid);

		void Init(int iTurn);

		const Vector2& GetLocation() const { return m_vLoc; }
		int GetPlayer() const { return m_iPlayer; }
		void SetPlayer(int iPlayer) { m_iPlayer = iPlayer; }

		void Reset() { m_bUpdated = false; m_bVisible = false; }
		void SetUpdated() { m_bUpdated = true; }
		void SetVisible() { m_bVisible = true; }

		bool IsNotUpdated() const { return m_bUpdated == false; }

#ifdef MYDEBUG
		void Draw(uint x, uint y, uint w, uint h, int iTurn, bool bSelect) const;
		void PrintInfo(sint16& x, sint16& y, sint16 yl) const;
#endif

	private:
		Vector2			m_vLoc;
		int				m_iPlayer;
		bool			m_bVisible;
		bool			m_bUpdated;

		const Grid&		m_oGrid;
		NavDijkstra		m_oDefense;

		vector<vector<Vector2>> m_aDefenseCount;
		uint				m_iBestDistDefense;

};

#endif //HILL_H_
