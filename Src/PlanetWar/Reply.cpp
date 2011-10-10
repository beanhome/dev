#define _USE_MATH_DEFINES
#include <cmath>

#include "Utils.h"
#include "PlanetWars.h"
#include "Reply.h"

Reply::Reply()
	: m_iId((uint16)-1)
	, m_iDemandId((uint16)-1)
	, m_iShipsCount((uint16)0)
	, m_iPropalPlanet((uint16)-1)
	, m_iDemandPlanet((uint16)-1)
{
	
}

Reply::Reply(uint16 iId, uint16 iDemandId, uint16 iShipCount, uint16 iPropalPanet, uint16 iDemandPlanet)
	: m_iId(iId)
	, m_iDemandId(iDemandId)
	, m_iShipsCount(iShipCount)
	, m_iPropalPlanet(iPropalPanet)
	, m_iDemandPlanet(iDemandPlanet)
{
}

Reply::Reply(const Reply& oPropal)
	: m_iId(oPropal.m_iId)
	, m_iDemandId(oPropal.m_iDemandId)
	, m_iShipsCount(oPropal.m_iShipsCount)
	, m_iPropalPlanet(oPropal.m_iPropalPlanet)
	, m_iDemandPlanet(oPropal.m_iDemandPlanet)
{
}


Reply::~Reply()
{
}


#ifdef MYDEBUG
void Reply::Log() const
{
	LOG("Reply %3d : (%3d -> %3d) [%3d]\n", GetID(), GetPropalPlanet(), GetDemandPlanet(), GetShipsCount());
}
#endif

