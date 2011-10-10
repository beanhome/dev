#ifndef SQUARE_H_
#define SQUARE_H_

#include "Utils.h"

class Square
{
	public:
		Square();

		void Init(const char* line, const char* sNext);
		void NewTurn();

		bool IsVisible() const { return m_bIsVisible; }
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

#ifdef MYDEBUG
		void Draw(uint x, uint y, uint w, uint h) const;
#endif

	private:
		bool m_bIsVisible;
		bool m_bIsWater;
		bool m_bIsFood;

		int m_iAntPlayer;
		int m_iHillPlayer;
    
		vector<int> m_aDeadAnts;
};

#endif //SQUARE_H_
