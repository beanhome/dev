#ifndef __FLEET_H__
#define __FLEET_H__

#include "Utils.h"

class Fleet
{
	friend class PlanetWars;

	public:
		// Initializes a fleet.
		Fleet();
		Fleet(const Fleet& oFleet);
		Fleet(uint16 iId, uint16 owner, uint16 num_ships, uint16 source_planet, uint16 destination_planet, sint16 start_turn, uint16 total_trip_length, uint16 turns_remaining);
		~Fleet();

		uint16 GetID() const { return m_iId; }

		uint16 GetOwner() const { return m_iOwner; }

		uint16 GetShipsCount() const { return m_iShipsCount; }

		uint16 GetSourcePlanet() const { return m_iSourcePlanet; }

		uint16 GetDestinationPlanet() const { return m_iDestinationPlanet; }

		uint16 GetTotalTripLength() const { return m_iTotalTripLength; }

		// Returns the number of turns until this fleet reaches its destination. If
		// this value is 1, then the fleet will hit the destination planet next turn.
		uint16 GetTurnsRemaining() const { return m_iTurnsRemaining; }

		sint16 GetStartTurn() const { return m_iStartTurn; }
		sint32 GetFinishTurn() const { return m_iStartTurn + m_iTotalTripLength; }

#ifdef MYDEBUG
		void Log() const;
		void Draw(uint iPlanetSelect = (uint)-1) const;
#endif

	private:
		uint16 				m_iId;
		uint16 				m_iOwner;
		uint16				m_iShipsCount;
		uint16				m_iSourcePlanet;
		uint16				m_iDestinationPlanet;
		sint16				m_iStartTurn;
		uint16				m_iTotalTripLength;
		uint16				m_iTurnsRemaining;

#ifdef MYDEBUG
	private:
		GraphicImage*		m_pImage;

#endif
};

typedef pair<uint, Fleet> FleetPair;
typedef map<uint, Fleet> FleetMap;



#endif
