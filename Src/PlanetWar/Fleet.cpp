#define _USE_MATH_DEFINES
#include <cmath>

#include "Utils.h"
#include "PlanetWars.h"
#include "Fleet.h"

Fleet::Fleet()
	: m_iId((uint16)-1)
	, m_iOwner((uint16)0)
	, m_iShipsCount((uint16)0)
	, m_iSourcePlanet((uint16)0)
	, m_iDestinationPlanet((uint16)0)
	, m_iStartTurn((sint16)0)
	, m_iTotalTripLength((uint16)0)
	, m_iTurnsRemaining((uint16)0)
#ifdef MYDEBUG
	, m_pImage(NULL)
#endif
{
	
}

Fleet::Fleet(uint16 iId, uint16 owner, uint16 num_ships, uint16 source_planet, uint16 destination_planet, sint16 start_turn, uint16 total_trip_length, uint16 turns_remaining)
	: m_iId(iId)
	, m_iOwner(owner)
	, m_iShipsCount(num_ships)
	, m_iSourcePlanet(source_planet)
	, m_iDestinationPlanet(destination_planet)
	, m_iStartTurn(start_turn)
	, m_iTotalTripLength(total_trip_length)
	, m_iTurnsRemaining(turns_remaining)
#ifdef MYDEBUG
	, m_pImage(NULL)
#endif
{
#ifdef MYDEBUG
	m_pImage = ge.LoadBMP(m_iOwner == 1 ? IMGDIR "FleetRed.bmp" : IMGDIR "FleetBlue.bmp");
#endif
}

Fleet::Fleet(const Fleet& oFleet)
	: m_iId(oFleet.m_iId)
	, m_iOwner(oFleet.m_iOwner)
	, m_iShipsCount(oFleet.m_iShipsCount)
	, m_iSourcePlanet(oFleet.m_iSourcePlanet)
	, m_iDestinationPlanet(oFleet.m_iDestinationPlanet)
	, m_iStartTurn(oFleet.m_iStartTurn)
	, m_iTotalTripLength(oFleet.m_iTotalTripLength)
	, m_iTurnsRemaining(oFleet.m_iTurnsRemaining)
#ifdef MYDEBUG
	, m_pImage(NULL)
#endif
{
#ifdef MYDEBUG
	if (oFleet.m_pImage != NULL)
		m_pImage = ge.CopyImage(oFleet.m_pImage);
	//m_pImage = ge.LoadBMP(m_iOwner == 1 ? "Images/FleetRed.bmp" : "Images/FleetBlue.bmp");
#endif
}


Fleet::~Fleet()
{
#ifdef MYDEBUG
	if (m_pImage != NULL)
		ge.FreeImage(m_pImage);
#endif
}


#ifdef MYDEBUG
void Fleet::Log() const
{
	LOG("Fleet : %3d (%3d -> %3d) [%3d] (%2i/%2u/%2d)\n", GetOwner(), GetSourcePlanet(), GetDestinationPlanet(), GetShipsCount(), GetStartTurn(), GetTurnsRemaining(), GetTotalTripLength());
}

void Fleet::Draw(uint iPlanetSelect) const
{
	Planet& oSrcPlanet = pw.GetPlanet(GetSourcePlanet());
	Planet& oDstPlanet = pw.GetPlanet(GetDestinationPlanet());

	float fSrcX = (float)oSrcPlanet.GetX();
	float fSrcY = (float)oSrcPlanet.GetY();
	float fDstX = (float)oDstPlanet.GetX();
	float fDstY = (float)oDstPlanet.GetY();
	float fDeltaX = fDstX - fSrcX;
	float fDeltaY = fDstY - fSrcY;
	float fLengthSq = fDeltaX * fDeltaX + fDeltaY * fDeltaY;
	float fLength = sqrt(fLengthSq);
	float fAlpha = max(1.f - (float)(GetTurnsRemaining()-1) / (float)(GetTotalTripLength()-1), 0.f);
	float fAngle = atan2f(-fDeltaY, fDeltaX);
	float fDirX = fDeltaX / fLength;
	float fDirY = fDeltaY / fLength;
	float fSrcRadius = Planet::GetRadius(oSrcPlanet.GetGrowthRate());
	float fDstRadius = Planet::GetRadius(oDstPlanet.GetGrowthRate());

	float x_pw = fSrcX + fDirX * fSrcRadius + (fDeltaX - fDirX * (fSrcRadius + fDstRadius)) * fAlpha;
	float y_pw = fSrcY + fDirY * fSrcRadius + (fDeltaY - fDirY * (fSrcRadius + fDstRadius)) * fAlpha;

	sint16 x, y;
	pw.ConvertSpace(x_pw, y_pw, x, y);

	uint8 r = 0;
	uint8 g = 0;
	uint8 b = 0;
	switch(GetOwner())
	{
	case 0:
		r = 160; g = 160; b = 160;
		break;
	case 1:
		r = 192; g = 0; b = 0;
		break;
	case 2:
		r = 0; g = 0; b = 192;
		break;
	}

	sint16 iRadius = 12;

	bool bHide = (iPlanetSelect < pw.GetAllPlanets().size() && GetSourcePlanet() != iPlanetSelect && GetDestinationPlanet() != iPlanetSelect);

	bool bSelect = false;
	if (gf_pw.IsMouseOverlapping(x, y, iRadius))
		bSelect = true;

	if (bHide == false || bSelect)
	{
		gf_pw.DrawImage(m_pImage, x, y, 180.f / (float)M_PI * fAngle, 0.18f);
		gf_pw.Print(x-(sint16)(fDirY*(float)iRadius), y+(sint16)(fDirX*(float)iRadius), 14, Center, r, g, b, "%d", GetShipsCount());
	}

	if (bSelect)
	{
		sint16 x_src, y_src;
		sint16 x_dst, y_dst;
		pw.ConvertSpace(fSrcX, fSrcY, x_src, y_src);
		pw.ConvertSpace(fDstX, fDstY, x_dst, y_dst);
		gf_pw.DrawLine(x_src, y_src, x_dst, y_dst, 40,40,40);

		gf_pw.Print(x-iRadius, y+iRadius, 10, LeftTop, 40,40,40, "ID %d", m_iId);
		gf_pw.Print(x-iRadius, y+iRadius+10, 10, LeftTop, 40,40,40, "%d/%d", GetTotalTripLength()-GetTurnsRemaining(), GetTotalTripLength());
	}

}

#endif

