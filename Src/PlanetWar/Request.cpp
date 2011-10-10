#define _USE_MATH_DEFINES
#include <cmath>

#include "Utils.h"
#include "PlanetWars.h"
#include "Request.h"

Request::Request()
	: m_iId((uint16)-1)
	, m_iShipsNeeded((uint16)0)
	, m_iSourcePlanet((uint16)0)
{
	
}

Request::Request(uint16 iId, uint16 iShipNeeded, uint16 iTurn, uint16 iSourcePlanet)
	: m_iId(iId)
	, m_iShipsNeeded(iShipNeeded)
	, m_iTurn(iTurn)
	, m_iSourcePlanet(iSourcePlanet)
{
}

Request::Request(const Request& oDemand)
	: m_iId(oDemand.m_iId)
	, m_iShipsNeeded(oDemand.m_iShipsNeeded)
	, m_iTurn(oDemand.m_iTurn)
	, m_iSourcePlanet(oDemand.m_iSourcePlanet)
{
}


Request::~Request()
{
}

float Request::GetCompletionPercentage() const
{

	return 0.f;
}


void Request::Cancel()
{
	{
		FleetMap::iterator begin = m_aFleet.begin();
		FleetMap::iterator end = m_aFleet.end();
		FleetMap::iterator it;
		for (it = begin ; it != end ; ++it)
		{
			pw.RemoveFleet(it->second.GetID());
		}
	}

	if (m_iSourceRequest != (uint16)-1)
	{
		Request& oSourceRequest = pw.GetRequest(m_iSourceRequest);

		oSourceRequest.OnRequestCanceled(m_iId);
	}

	{
		RequestMap::iterator begin = m_aRequest.begin();
		RequestMap::iterator end = m_aRequest.end();
		RequestMap::iterator it;
		for (it = begin ; it != end ; ++it)
		{
			pw.RemoveRequest(it->second.GetID());
		}
	}
}

void Request::OnFleetCanceled(uint16 id)
{
	FleetMap::iterator it = m_aFleet.find(id);
	ASSERT(it != m_aFleet.end());

	m_aFleet.erase(it);
}

void Request::OnRequestCanceled(uint16 id)
{
	RequestMap::iterator it = m_aRequest.find(id);
	ASSERT(it != m_aRequest.end());

	m_aRequest.erase(it);
}


#ifdef MYDEBUG
void Request::Log() const
{
	LOG("Request %3d : %3d [%3d]\n", GetID(), GetSourcePlanet(), GetShipsNeeded());
}
#endif

