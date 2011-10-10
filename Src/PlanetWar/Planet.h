#ifndef __PLANET_H__
#define __PLANET_H__

#include <vector>
#include <set>
#include <map>

#include "Utils.h"

//#include "Demand.h"
//#include "Propal.h"

#ifdef MYDEBUG
#include "Graphic.h"
#endif

class PlanetWars;
class Fleet;
class Planet;

struct NextTurn
{
	uint16 m_iOwner;
	sint16 m_iShipCount;
	sint16 m_iShipGrowth[3];
	sint16 m_iShipNeededMin;
	sint16 m_iShipNeededMax;
	set<uint16> m_aFleets;

	NextTurn()
		: m_iOwner(0)
		, m_iShipCount(0)
	{
		m_iShipGrowth[0] = 0;
		m_iShipGrowth[1] = 0;
		m_iShipGrowth[2] = 0;
	}
};

struct PositionOrderer;

class Planet
{
	friend class PlanetWars;

	public:
		/*
		typedef map<uint16, Demand> DemandSendMap;
		typedef pair<uint16, Demand> DemandSendPair;
		typedef multimap<float, Demand> DemandReceiveMap;
		typedef pair<float, Demand> DemandReceivePair;

		typedef map<uint, Propal> PropalSendMap;
		typedef pair<uint, Propal> PropalSendPair;
		typedef multimap<uint16, Propal> PropalReceiveMap;
		typedef pair<uint16, Propal> PropalReceivePair;
		*/
		typedef multimap<float, Planet*, greater<float> > PositionOrderedPlanet;
		typedef multimap<uint16, const Planet*, less<float> > DistanceOrderedPlanetMap;
		typedef pair<uint16, const Planet*> DistanceOrderedPlanetPair;

		// Initializes a planet.
		Planet(int planet_id,
			int owner,
			int num_ships,
			int growth_rate,
			float x,
			float y);
		
		~Planet();

		void				RegisterPlanet(const Planet* pPlanet);

		// Returns the ID of this planets. Planets are numbered starting at zero.
		uint16 				GetPlanetID() const { return m_iPlanetId; }

		// Returns the ID of the player that owns this planet. Your playerID is
		// always 1. If the owner is 1, this is your planet. If the owner is 0, then
		// the planet is neutral. If the owner is 2 or some other number, then this
		// planet belongs to the enemy.
		uint16				GetOwner(uint iTurn=0) const; // { return m_iOwner; }

		// The number of ships on the planet. This is the "population" of the planet.
		uint16 				GetShipsCount(uint iTurn=0, uint iTesterOwner=1) const;
		//sint32 				GetPotentialShipsCount(uint iTurn, uint16 iInitialShipCount) const;
		int 				GetRealShipsCount() const { return m_iShipsCount; }

		sint16				GetShipsCapacity() const { return m_iShipsCapacity; }
		sint16				GetShipsCapacityFor(const Planet& oOtherPlanet) const;
		sint16				GetShipsNeeded(uint iDist) const;
		sint16				GetShipsNeeded(uint iDist, sint16& iMaxNeeded) const;

		// Returns the growth rate of the planet. Unless the planet is neutral, the
		// population of the planet grows by this amount each turn. The higher this
		// number is, the faster this planet produces ships.
		uint16 				GetGrowthRate() const { return m_iGrowthRate; }

		// The position of the planet in space.
		float 				GetX() const { return m_fX; }
		float 				GetY() const { return m_fY; }


		const NextTurn&		GetNextTurn(uint i) const { return m_aNextTurn[i]; }

		//void 				SetOwner(int new_owner) { m_iOwner = new_owner; }
		//void 				SetShipsCount(int new_num_ships) { m_iShipsCount = new_num_ships; }

		//void 				AddShips(int amount);
		void 				RemoveRealShips(sint16 amount);
		void 				RemoveShips(sint16 amount);

		void 				ApplyFleet(int iOwner, uint iAmount, uint iTurn);

		void 				AddFleet(const Fleet& pFleet);	
		void 				RemoveFleet(const Fleet& oFleet);
		void 				Compute();
		void 				ComputeInfluence();
		float 				GetInfluenceOn(const Planet& oPlanet) const;

		bool				IsLosingOwner(sint16 iStartTurn = 0) const;
		bool				IsLosingOwner(sint16 iStartTurn, uint16& iLosingTurn, uint16& iOwner) const;
		bool				IsUnderAttack(uint16 iOwner, uint16& iTurn, uint16& iShipcount) const;


		float				ValuateFor(const Planet& oPlanet, float* pval1=NULL, float* pval2=NULL, float* pval3=NULL) const;
		float				Valuate() const;
		float				ValuateDanger(float* pval1=NULL, float* pval2=NULL, float* pval3=NULL) const;

		float				GetGrowth(uint iTurn, uint iOwner) const;

		//float				GetDanger() const { return m_fDanger; }
		float				GetOwnedInfluence() const { return m_fOwnedInfluence; }
		float				GetEnemyInfluence() const { return m_fEnemyInfluence; }
		float				GetInfluence() const { return m_fInfluence; }


		void				BroadcastDemand();
		bool				TestSetOfPlanet(PositionOrderedPlanet& aPositionOrderedPlanet, uint16* tab, uint size, float& fMinShipRatio, float& fMaxShipRatio, uint16& iMaxDist);

		/*
		void				CreateAndBroadcastDemand();
		void				ReceiveDemand(const Demand& oDemand);
		void				RespondToDemand();
		void				ReceivePropal(const Propal& oPropal);
		void				ValidatePropal();
		void				AcceptPropal(const Propal& oPropal);
		void				DeletePropal(const Propal& oPropal);
		*/


#ifdef MYDEBUG
		void				Log(uint iNextTurnLog) const;
		void				Draw(uint iPlanetSelect = (uint)-1) const;
		static float		GetRadius(uint iGrowthRate);
		static float		ConvertRadius(float fRadius);
#endif

	public:
		static uint16		GetDistance(const Planet& SrcPlanet, const Planet& DstPlanet);

	private:
		uint16							m_iPlanetId;
		uint16							m_iGrowthRate;
		float							m_fX;
		float							m_fY;

		uint16							m_iOwner;
		sint16							m_iShipsCount;
		sint16							m_iShipsCapacity;

		NextTurn						m_aNextTurn[MAX_TURN];
		DistanceOrderedPlanetMap		m_aPlanets;

		uint16							m_iNextOwner; // different if losing Owner
		uint16							m_iLoseOwnerTurn;
		uint16							m_iBestTurn;

		float							m_fOwnedInfluence;
		float							m_fEnemyInfluence;
		float							m_fInfluence;

		/*
		uint16							m_iDemandCounter;
		DemandSendMap					m_aDemandSend;
		DemandReceiveMap				m_aDemandReceive;
		uint16							m_iPropalCounter;
		PropalSendMap					m_aPropalSend;
		PropalReceiveMap				m_aPropalReceive;
		*/

#ifdef MYDEBUG
		GraphicImage*					m_pImage;
#endif

	public:
		static const float	s_fInfluenceCoeff;
		static const float	s_fNeutralValueCoeff;
		static const float	s_fNeutralUnderNMEAttackCoeff;
		static const float	s_fNeutralInfluenceThreshold;
		static const float	s_fNeutralInfluenceCoeff;

		static const float	s_fOwnedLosingCoeff;
		static const float	s_fOwnedUnderNMEAttackCoeff;
		static const float	s_fOwnedPositionCoeff;
		static const float	s_fOwnedGrowthCoeff;

		static const float	s_fEnemyValueCoeff;
		static const float	s_fEnemyUnderAttackCoeff;
		static const float	s_fEnemyInfluenceThreshold;
		static const float	s_fEnemyInfluenceCoeff;

};

struct InterestOrderer
{
	bool operator()(const Planet* p1, const Planet* p2)
	{
		float fValCoeff = 1.f;

		float val1 = p1->Valuate() * fValCoeff;
		float pos1 = p1->GetInfluence();

		float val2 = p2->Valuate() * fValCoeff;
		float pos2 = p1->GetInfluence();

		if (p1->GetOwner() == 1 && p2->GetOwner() != 1)
		{
			return true;
		}
		else if (p1->GetOwner() != 1 && p2->GetOwner() == 1)
		{
			return false;
		}
		else if (p1->GetOwner() == 1 && p2->GetOwner() == 1)
		{
			return (val1 != val2 ? val1 < val2 : pos1 < pos2);
		}
		else
		{
			return (val1 > val2);
		}
	}
};

struct PositionOrderer
{
	bool operator()(const Planet* p1, const Planet* p2)
	{
		return (p1->GetInfluence() > p2->GetInfluence());
	}
};



#endif
