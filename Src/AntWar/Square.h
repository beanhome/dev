#ifndef SQUARE_H_
#define SQUARE_H_

#include "Utils.h"

class Square
{
	public:
		Square();

		void Init(const char* line, const char* sNext, int iTurn);
		void NewTurn();

		bool IsVisible() const { return m_bIsVisible; }
		bool IsDiscovered(int iTurn) const { return (m_iDiscoveredTurn > -1 && m_iDiscoveredTurn <= iTurn); }
		bool IsWater() const { return m_bIsWater; }
		bool IsFood() const { return m_bIsFood; }

		bool HasAnt() const { return m_iAntPlayer != -1; }
		bool HasFriendAnt() const { return m_iAntPlayer == 0; }
		bool HasEnemyAnt() const { return m_iAntPlayer > 0; }
		int  GetAntPlayer() const { return m_iAntPlayer; }

		bool IsHill() const { return m_iHillPlayer != -1; }
		bool IsFriendHill() const { return m_iHillPlayer == 0; }
		bool IsEnemyHill() const { return m_iHillPlayer > 0; }
		int  GetHillPlayer() const { return m_iHillPlayer; }

		bool HasDeadAnt() const { return m_aDeadAnts.size() > 0; }

		void SetAntPlayer(int player) { m_iAntPlayer = player; }
		void SetVisible(bool bVisible = true) { m_bIsVisible = bVisible; }
		
		void SetDiscovered(int iTurn) { if (m_iDiscoveredTurn == -1) m_iDiscoveredTurn = iTurn; }

#ifdef MYDEBUG
		void Draw(uint x, uint y, uint w, uint h, int iTurn, bool bSelect) const;
		void PrintInfo(sint16& x, sint16& y, sint16 yl, int iTurn) const;
#endif

	private:
		int m_iDiscoveredTurn;
		bool m_bIsVisible;
		bool m_bIsWater;
		bool m_bIsFood;

		int m_iAntPlayer;
		int m_iHillPlayer;

		struct DeadAnt
		{
			DeadAnt(int iTurn, int iPlayer) : m_iTurn(iTurn), m_iPlayer(iPlayer) {}
			
			int m_iTurn;
			int m_iPlayer;
		};
		vector<DeadAnt> m_aDeadAnts;
};

#endif //SQUARE_H_
