#ifndef SQUARE_H_
#define SQUARE_H_

#include "Utils.h"

enum DrawMode
{
	EDM_Normal,
	EDM_Influence,
};


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

		void AddInfluence(int iVal);
		int  GetAntInfluence() const { return m_iAntInfluence; }

		int  GetBadInfluenceOf(int iPlayer) { return m_aBadInfluence[iPlayer]; }
		int  GetBadInfluenceFor(int iPlayer);
		void AddBadInfluence(int iPlayer, int val=1) { m_aBadInfluence[iPlayer] += val; }
		void RemBadInfluence(int iPlayer, int val=1) { m_aBadInfluence[iPlayer] -= val; }

		bool IsBlock(int iTurn, int iDist=0) const { return (!IsDiscovered(iTurn) || IsWater() || (GetAntInfluence() <= 0) || /*IsFriendHill() ||*/ (iDist == 1 && HasFriendAnt())); }

#ifdef MYDEBUG
		void Draw(uint x, uint y, uint w, uint h, int iTurn, bool bSelect, DrawMode mode) const;
		void PrintInfo(sint16& x, sint16& y, sint16 yl, int iTurn) const;
#endif

	public:
		static const int s_iNoInfluence = 0x7FFFFFFF;

	private:
		int					m_iDiscoveredTurn;
		bool				m_bIsVisible;
		bool				m_bIsWater;
		bool				m_bIsFood;

		int					m_iAntPlayer;
		int					m_iHillPlayer;

		int					m_iAntInfluence; // deprecated ??

		struct DeadAnt
		{
			DeadAnt(int iTurn, int iPlayer) : m_iTurn(iTurn), m_iPlayer(iPlayer) {}
			
			int m_iTurn;
			int m_iPlayer;
		};
		vector<DeadAnt>		m_aDeadAnts;

		map<int, int>		m_aBadInfluence;

};

#endif //SQUARE_H_
