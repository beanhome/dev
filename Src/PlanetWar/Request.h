#ifndef __DEMAND_H__
#define __DEMAND_H__

#include "Utils.h"

class Request;

typedef pair<uint, Request> RequestPair;
typedef map<uint, Request> RequestMap;

class Request
{
	friend class PlanetWars;

	public:
		Request();
		Request(const Request& oRequest);
		Request(uint16 iId, uint16 iShipNeeded, uint16 iTurn, uint16 iSourcePlanet);
		~Request();

		uint16 GetID() const { return m_iId; }

		uint16 GetShipsNeeded() const { return m_iShipsNeeded; }
		uint16 GetTurn() const { return m_iTurn; }

		uint16 GetSourcePlanet() const { return m_iSourcePlanet; }

		float GetCompletionPercentage() const;

		void Cancel();
		void OnFleetCanceled(uint16 iId);
		void OnRequestCanceled(uint16 iId);

#ifdef MYDEBUG
		void Log() const;
#endif

	private:
		uint16 				m_iId;
		uint16				m_iShipsNeeded;
		uint16				m_iTurn;
		uint16				m_iSourcePlanet;
		
		uint16				m_iSourceRequest; // en réponse à un autre Request

		
		FleetMap			m_aFleet; // liste des fleet
		RequestMap			m_aRequest; // liste des request 
};



#endif
