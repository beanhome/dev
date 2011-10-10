#include "PlanetWars.h"
#include "Time.h"


#ifdef MYDEBUG
#include "Graphic.h"
#endif

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void StringUtil::Tokenize(const string& s, const string& delimiters, vector<string>& tokens)
{
	string::size_type lastPos = s.find_first_not_of(delimiters, 0);
	string::size_type pos = s.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(s.substr(lastPos, pos - lastPos));
		lastPos = s.find_first_not_of(delimiters, pos);
		pos = s.find_first_of(delimiters, lastPos);
	}
}

vector<string> StringUtil::Tokenize(const string& s, const string& delimiters)
{
	vector<string> tokens;
	Tokenize(s, delimiters, tokens);
	return tokens;
}

PlanetWars::PlanetWars()
#ifdef MYDEBUG
	: m_bKeyDown(false)
	, m_iKeyDownTime(0)
	, m_iRepeatDelay(0)
	, m_iFirstRepeatDelay(500)
	, m_iNextRepeatDelay(30)
#endif
{
#ifdef MYDEBUG
	m_pBG = ge.LoadBMP(IMGDIR "Background.bmp");
#endif
}

PlanetWars::~PlanetWars()
{
#ifdef MYDEBUG
	ge.FreeImage(m_pBG);
#endif
}

void PlanetWars::NewTurn(uint16 iTurnNumber, const string& gameState, bool bInverted)
{
	m_iTurnNumber = iTurnNumber;
	m_iFleetCounter = 0;
	m_iRequestCounter = 0;

	Clear();

	ParseGameState(gameState, bInverted);
	m_fSize = sqrt(m_fWidth*m_fWidth+m_fHeight*m_fHeight);

	ComputeData();
}

void PlanetWars::Clear()
{
	m_aOwnedPlanets.clear();
	m_aNotOwnedPlanets.clear();
	m_aEnemyPlanets.clear();
	m_aNeutralPlanets.clear();
	m_aOwnedFleets.clear();
	m_aEnemyFleets.clear();

	m_aPlanets.clear();
	m_aFleets.clear();

	m_iFleetCounter = 0;
	m_iRequestCounter = 0;

	m_iTotalOwnedPlanetCount = 0;
	m_iTotalEnemyPlanetCount = 0;
	m_iTotalOwnedShipCount = 0;
	m_iTotalEnemyShipCount = 0;
	m_iTotalOwnedGrowthRate = 0;
	m_iTotalEnemyGrowthRate = 0;

	m_fMaxInfluence = 0.f;
	m_fMinInfluence = 0.f;
}


const Planet& PlanetWars::GetPlanet(int planet_id) const
{
	return m_aPlanets[planet_id];
}

Planet& PlanetWars::GetPlanet(int planet_id)
{
	return m_aPlanets[planet_id];
}

const Fleet& PlanetWars::GetFleet(int fleet_id) const
{
	FleetMap::const_iterator it = m_aFleets.find(fleet_id);

	ASSERT(it != m_aFleets.end());

	return it->second;
}

uint16 PlanetWars::GetDistance(int source_planet, int destination_planet) const
{
	const Planet& source = m_aPlanets[source_planet];
	const Planet& destination = m_aPlanets[destination_planet];
	return Planet::GetDistance(source, destination);
}

void PlanetWars::AddPlanet(uint iId, uint iOwner, uint iShipCount, uint iGrowthRate, float fX, float fY)
{
	Planet p(iId, iOwner, iShipCount, iGrowthRate, fX, fY);
	m_aPlanets.push_back(p);

	if (m_fWidth < p.GetX())
		m_fWidth = (float)p.GetX();

	if (m_fHeight < p.GetY())
		m_fHeight = (float)p.GetY();

	switch (iOwner)
	{
		case 1:
			m_iTotalOwnedPlanetCount += iShipCount;
			m_iTotalOwnedShipCount += iShipCount;
			m_iTotalOwnedGrowthRate += iGrowthRate;
			break;

		case 2:
			m_iTotalEnemyPlanetCount += iShipCount;
			m_iTotalEnemyShipCount += iShipCount;
			m_iTotalEnemyGrowthRate += iGrowthRate;
			break;
	}
}


void PlanetWars::AddFleet(uint16 iOwner, uint16 iShipCount, uint16 iSourcePlanet, uint16 iDestinationPlanet, uint16 iTotalTripLength, uint16 iTurnsRemaining)
{
	uint16 Id = m_iFleetCounter++;
	sint16 iStartTurn = iTurnsRemaining - iTotalTripLength;

	Fleet oFleet(Id, iOwner, iShipCount, iSourcePlanet, iDestinationPlanet, iStartTurn, iTotalTripLength, iTurnsRemaining);
	m_aFleets.insert(FleetPair(Id, oFleet));

	Planet& SrcPlanet = GetPlanet(oFleet.GetSourcePlanet());
	SrcPlanet.AddFleet(oFleet);

	Planet& DstPlanet = GetPlanet(oFleet.GetDestinationPlanet());
	DstPlanet.AddFleet(oFleet);

	switch (iOwner)
	{
		case 1:	    m_iTotalOwnedShipCount += iShipCount;   break;
		case 2:     m_iTotalEnemyShipCount += iShipCount;   break;
	}
}

uint16 PlanetWars::CreateFleet(uint16 iOwner, uint16 iShipCount, uint16 iSourcePlanet, uint16 iDestinationPlanet, sint16 iStartTurn)
{
	uint16 Id = m_iFleetCounter++;
	uint16 iTotalTripLength = GetDistance(iSourcePlanet, iDestinationPlanet);
	uint16 iTurnsRemaining = iTotalTripLength;

	Fleet oFleet(Id, iOwner, iShipCount, iSourcePlanet, iDestinationPlanet, iStartTurn, iTotalTripLength, iTurnsRemaining);

	m_aFleets.insert(FleetPair(Id, oFleet));

	Planet& SrcPlanet = GetPlanet(oFleet.GetSourcePlanet());
	if (iStartTurn == 0)
	{
		RemoveInfluence(SrcPlanet);
		switch (iOwner)
		{
			case 1:		m_iTotalOwnedPlanetCount -= iShipCount;		break;
			case 2:		m_iTotalEnemyPlanetCount -= iShipCount;		break;
			default:	break;
		}
	}
	SrcPlanet.AddFleet(oFleet);
	SrcPlanet.Compute();
	if (iStartTurn == 0)
		ApplyInfluence(SrcPlanet);

	Planet& DstPlanet = GetPlanet(oFleet.GetDestinationPlanet());
	//DstPlanet.RemoveMyInfluence(); inutile puisque au dela du tour 0
	DstPlanet.AddFleet(oFleet);
	DstPlanet.Compute();
	//DstPlanet.ApplyMyInfluence();

	switch (iOwner)
	{
		case 1:	    m_iTotalOwnedShipCount += iShipCount;   break;
		case 2:     m_iTotalEnemyShipCount += iShipCount;   break;
	}

	return oFleet.GetID();
}

void PlanetWars::EditFleet(uint16 id, uint16 iShipCount, sint16 iStartTurn)
{
	FleetMap::iterator it = m_aFleets.find(id);
	ASSERT(it != m_aFleets.end());
	Fleet& oFleet = it->second;

	CHECK_RETURN(oFleet.GetStartTurn() >= 0, "Error : try to edit an flying Fleet\n");

	Planet& SrcPlanet = GetPlanet(oFleet.GetSourcePlanet());
	Planet& DstPlanet = GetPlanet(oFleet.GetDestinationPlanet());

	if (iStartTurn == 0)
		RemoveInfluence(SrcPlanet);

	SrcPlanet.RemoveFleet(oFleet);
	DstPlanet.RemoveFleet(oFleet);

	oFleet.m_iShipsCount = iShipCount;
	oFleet.m_iStartTurn = iStartTurn;

	SrcPlanet.AddFleet(oFleet);
	DstPlanet.AddFleet(oFleet);

	SrcPlanet.Compute();
	DstPlanet.Compute();

	if (iStartTurn == 0)
		ApplyInfluence(SrcPlanet);
}

void PlanetWars::RemoveFleet(uint16 id)
{
	//LOG("Suppression du Fleet %d\n", id);

	FleetMap::iterator it = m_aFleets.find(id);
	ASSERT(it != m_aFleets.end());
	Fleet& oFleet = it->second;

	Planet& SrcPlanet = GetPlanet(oFleet.GetSourcePlanet());
	if (oFleet.GetStartTurn() == 0)
		RemoveInfluence(SrcPlanet);
	SrcPlanet.RemoveFleet(oFleet);
	SrcPlanet.Compute();
	if (oFleet.GetStartTurn() == 0)
		ApplyInfluence(SrcPlanet);

	Planet& DstPlanet = GetPlanet(oFleet.GetDestinationPlanet());
	DstPlanet.RemoveFleet(oFleet);
	DstPlanet.Compute();

	m_aFleets.erase(it);
}

Request& PlanetWars::GetRequest(uint16 id)
{
	RequestMap::iterator it = m_aRequest.find(id);
	ASSERT(it != m_aRequest.end());

	return it->second;
}

const Request& PlanetWars::GetRequest(uint16 id) const
{
	RequestMap::const_iterator it = m_aRequest.find(id);
	ASSERT(it != m_aRequest.end());

	return it->second;
}


void PlanetWars::AddRequest(uint16 iSrcPlanet, uint16 iShipNeeded, uint16 iTurn)
{
	uint16 iID = m_iRequestCounter++;
	m_aRequest.insert(RequestPair(iID, Request(iID, iShipNeeded, iTurn, iSrcPlanet)));
}

void PlanetWars::RemoveRequest(uint16 iID)
{
	RequestMap::iterator it = m_aRequest.find(iID);
	ASSERT(it != m_aRequest.end());
	
	Request& oRequest = it->second;

	oRequest.Cancel();

	m_aRequest.erase(it);
}


/*
void PlanetWars::CreateOrder(int iSourcePlanet, int iDestinationPlanet, int iShipCount)
{	
	int iDist = GetDistance(iSourcePlanet, iDestinationPlanet);
	Fleet oFleet(1, iShipCount, iSourcePlanet, iDestinationPlanet, iDist, iDist, Test);

	AddFleet(oFleet);
}
*/

void PlanetWars::IssueOrder(int source_planet, int destination_planet, int num_ships) const
{
	LOG("IssueOrder : (%3d -> %3d) [%3d]\n", source_planet, destination_planet, num_ships);

	CHECK_RETURN(GetPlanet(source_planet).GetOwner() == 1, "Error : Bad Source Planet\n");
	CHECK_RETURN(source_planet != destination_planet, "Error : Same Planet\n");
	CHECK_RETURN(GetPlanet(source_planet).GetRealShipsCount() >= num_ships, "Error : Too many Ship (%d pour %d)\n", num_ships, GetPlanet(source_planet).GetRealShipsCount());
	CHECK_RETURN(num_ships > 0, "Error : Negative ship count\n");

	cout << source_planet << " " << destination_planet << " " << num_ships << endl;
	cout.flush();
}

void PlanetWars::ExecuteOrders()
{
	FleetMap::const_iterator begin = m_aFleets.begin();
	FleetMap::const_iterator end = m_aFleets.end();
	FleetMap::const_iterator it;

	for (it = begin ; it != end ; ++it)
	{
		if (it->second.GetStartTurn() == 0)
		{
			IssueOrder(it->second.GetSourcePlanet(), it->second.GetDestinationPlanet(), it->second.GetShipsCount());
			GetPlanet(it->second.GetSourcePlanet()).RemoveRealShips(it->second.GetShipsCount());
		}
	}
}


void PlanetWars::FinishTurn() const
{
	cout << "go" << endl;
	cout.flush();

	LOG("\n\n");
}


bool PlanetWars::IsAlive(uint player_id) const
{
	for (unsigned int i = 0; i < m_aPlanets.size(); ++i)
	{
		if (m_aPlanets[i].GetOwner() == player_id)
		{
			return true;
		}
	}

	FleetMap::const_iterator begin = m_aFleets.begin();
	FleetMap::const_iterator end = m_aFleets.end();
	FleetMap::const_iterator it;

	for (it = begin ; it != end ; ++it)
	{
		if (it->second.GetOwner() == player_id)
		{
			return true;
		}
	}
	return false;
}

int PlanetWars::ParseGameState(const string& s, bool bInverted)
{
	m_aPlanets.clear();
	m_aFleets.clear();
	m_fWidth = 0.f;
	m_fHeight = 0.f;

	vector<string> lines = StringUtil::Tokenize(s, "\n");

	int planet_id = 0;
	for (unsigned int i = 0; i < lines.size(); ++i)
	{
		string& line = lines[i];

		size_t comment_begin = line.find_first_of('#');
		if (comment_begin != string::npos)
		{
			line = line.substr(0, comment_begin);
		}
		vector<string> tokens = StringUtil::Tokenize(line);
		if (tokens.size() == 0)
		{
			continue;
		}

		if (tokens[0] == "P")
		{
			if (tokens.size() != 6)
			{
				return 0;
			}

			int iOwner = atoi(tokens[3].c_str());
			if (bInverted && iOwner > 0)
				iOwner = 3 - iOwner;

			AddPlanet(planet_id++,        // The ID of this planet
				iOwner,  // Owner
				atoi(tokens[4].c_str()),  // Num ships
				atoi(tokens[5].c_str()),  // Growth rate
				(float)atof(tokens[1].c_str()),  // X
				(float)atof(tokens[2].c_str())); // Y
		}
		else if (tokens[0] == "F")
		{
			if (tokens.size() != 7)
			{
				return 0;
			}

			AddFleet((bInverted ? (uint16)(3-atoi(tokens[1].c_str())) : (uint16)atoi(tokens[1].c_str())),  // Owner
				(uint16)atoi(tokens[2].c_str()),       // Num ships
				(uint16)atoi(tokens[3].c_str()),       // Source
				(uint16)atoi(tokens[4].c_str()),       // Destination
				(uint16)atoi(tokens[5].c_str()),       // Total trip length
				(uint16)atoi(tokens[6].c_str()));      // Turns remaining
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

void PlanetWars::ComputeData()
{
	for (uint i=0 ; i<m_aPlanets.size() ; ++i)
	{
		switch (m_aPlanets[i].GetOwner())
		{
			case 0:
				m_aNeutralPlanets.push_back(&m_aPlanets[i]);
				m_aNotOwnedPlanets.push_back(&m_aPlanets[i]);
				break;

			case 1:
				m_aOwnedPlanets.push_back(&m_aPlanets[i]);
				break;

			case 2:
				m_aEnemyPlanets.push_back(&m_aPlanets[i]);
				m_aNotOwnedPlanets.push_back(&m_aPlanets[i]);
				break;
		}

		for (uint j=0 ; j<m_aPlanets.size() ; ++j)
		{
			if (i==j)
				continue;

			m_aPlanets[i].RegisterPlanet(&m_aPlanets[j]);
		}

		m_aPlanets[i].Compute();
		m_aPlanets[i].ComputeInfluence();
		//m_aPlanets[i].ValuateDanger();
	}
}

void PlanetWars::RemoveInfluence(const Planet& oPlanetToRemove)
{
	for (uint i=0 ; i<m_aPlanets.size() ; ++i)
	{
		Planet& oPlanet = m_aPlanets[i];

		if (oPlanet.GetPlanetID() == oPlanetToRemove.GetPlanetID())
			continue;

		float fInfluence = oPlanetToRemove.GetInfluenceOn(oPlanet);

		switch (oPlanetToRemove.GetOwner())
		{
		case 0:
			continue;
			break;

		case 1:
			oPlanet.m_fOwnedInfluence -= fInfluence;
			break;

		case 2:
			oPlanet.m_fEnemyInfluence -= fInfluence;
			break;
		}
	}
}

void PlanetWars::ApplyInfluence(const Planet& oPlanetToApply)
{
	for (uint i=0 ; i<m_aPlanets.size() ; ++i)
	{
		Planet& oPlanet = m_aPlanets[i];

		if (oPlanet.GetPlanetID() == oPlanetToApply.GetPlanetID())
			continue;

		float fInfluence = oPlanetToApply.GetInfluenceOn(oPlanet);

		switch (oPlanetToApply.GetOwner())
		{
		case 0:
			continue;
			break;

		case 1:
			oPlanet.m_fOwnedInfluence += fInfluence;
			break;

		case 2:
			oPlanet.m_fEnemyInfluence += fInfluence;
			break;
		}
	}
}

void PlanetWars::RegisterInfluence(float fInfluence)
{
	m_fMaxInfluence = max(m_fMaxInfluence, fInfluence);
	m_fMinInfluence = min(m_fMinInfluence, fInfluence);
}

#ifdef MYDEBUG
void PlanetWars::ConvertSpace(float x_in, float y_in, sint16& x_out, sint16& y_out) const
{
	float margin = Planet::ConvertRadius(Planet::GetRadius(6));
	x_out = (sint16)(margin + x_in * ((float)gf_pw.GetWidth() - margin * 2.f) / m_fWidth);
	y_out = (sint16)(margin + y_in * ((float)gf_pw.GetHeight() - margin * 2.f) / m_fHeight);
}

void PlanetWars::Draw(bool bPostCompute, uint iPlanetSelect)
{
	ge.Clear();

	//DrawImage(m_pBG);

	for (uint i=0 ; i<m_aPlanets.size() ; ++i)
	{
		m_aPlanets[i].Draw(iPlanetSelect);
	}

	for (uint i=0 ; i<m_aFleets.size() ; ++i)
	{
		m_aFleets[i].Draw(iPlanetSelect);
	}

	gf_pw.Print((sint16)gf_pw.GetWidth() / 2, 10, 16, Center, 0, 0, 0, "Turn %d %s", m_iTurnNumber, (bPostCompute ? "Computed" : ""));
	
	gf_pw.Print(0 , 0, 14, LeftTop, 0, 0, 0, "Total Ship count %d %d", m_iTotalOwnedShipCount, m_iTotalEnemyShipCount);
	gf_pw.Print(0 , 14, 14, LeftTop, 0, 0, 0, "Total Rate %d %d", m_iTotalOwnedGrowthRate, m_iTotalEnemyGrowthRate);

	ge.Flip();
}

uint16 PlanetWars::DrawLoop(bool bPostCompute)
{
	bool bContinue = false;
	uint16 iRound = m_iTurnNumber;
	
	while(!bContinue)
	{
		uint iPlanetSelect = m_aPlanets.size();

		for (uint i=0 ; i<m_aPlanets.size() ; ++i)
		{
			sint16 x, y;
			ConvertSpace(m_aPlanets[i].GetX(), m_aPlanets[i].GetY(), x, y);
			sint16 iRadius = (sint16)Planet::ConvertRadius(Planet::GetRadius(m_aPlanets[i].GetGrowthRate()));

			if (gf_pw.IsMouseOverlapping(x, y, iRadius))
			{
				iPlanetSelect = i;
				break;
			}
		}

		Draw(bPostCompute, iPlanetSelect);

		const SDL_Event& oSDLEvent = ge.PollEvent();
		switch(oSDLEvent.type)
		{
			case SDL_QUIT:
			{
				return (uint16)-1;
			}

			case SDL_KEYDOWN:
			{
				if (!m_bKeyDown)
				{
					m_iKeyDownTime = GetTime();
					m_iRepeatDelay = m_iFirstRepeatDelay;
				}
				else
				{
					if (GetTime() > m_iKeyDownTime + m_iRepeatDelay)
					{
						m_bKeyDown = false;
						m_iKeyDownTime = GetTime();
						m_iRepeatDelay = m_iNextRepeatDelay;
					}
				}

				if (!m_bKeyDown)
				{
					switch(oSDLEvent.key.keysym.sym)
					{
						case SDLK_LEFT:
							if (iRound > 0)
							{
								bContinue = true;
								iRound--;
							}
							break;
	
						case SDLK_RIGHT:
							bContinue = true;
							iRound++;
							break;
	
						case SDLK_SPACE:
							bContinue = true;
							break;
					}
				}

				m_bKeyDown = true;

				break;
			}

			case SDL_KEYUP:
			{
				m_bKeyDown = false;
				break;
			}

		}
	}

	return iRound;
}

#endif




