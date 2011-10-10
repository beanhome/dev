#ifndef __PROPAL_H__
#define __PROPAL_H__

#include "Utils.h"

class Reply
{
	friend class PlanetWars;

	public:
		Reply();
		Reply(const Reply& oPropal);
		Reply(uint16 iId, uint16 iDemandId, uint16 iShipCount, uint16 iPropalPanet, uint16 iDemandPlanet);
		~Reply();

		uint16 GetID() const { return m_iId; }
		
		uint16 GetDemandID() const { return m_iDemandId; }

		uint16 GetShipsCount() const { return m_iShipsCount; }
		void SetShipCount(uint16 iShipcount) {m_iShipsCount = iShipcount; }

		uint16 GetPropalPlanet() const { return m_iPropalPlanet; }

		uint16 GetDemandPlanet() const { return m_iDemandPlanet; }

#ifdef MYDEBUG
		void Log() const;
#endif

	private:
		uint16 				m_iId;
		uint16 				m_iDemandId;
		uint16				m_iShipsCount;
		uint16				m_iPropalPlanet;
		uint16				m_iDemandPlanet;
};

#endif
