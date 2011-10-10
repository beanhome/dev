#include <iostream>
#include <vector>

#include "Utils.h"
#include "PlanetWars.h"
#include "Planet.h"
#include "Fleet.h"

#ifdef MYDEBUG
void PrintPlanet(char* sTitle);
#endif

void DoTurn() 
{
	LOG("Turn %d\n\n", pw.GetTurnNumber());

#ifdef MYDEBUG
	PrintPlanet("Pre Order :");
#endif

	typedef multiset<Planet*, InterestOrderer> InterestOrderedPlanet;
	InterestOrderedPlanet aInterestOrderedPlanet;

	for (uint i=0 ; i<pw.GetAllPlanets().size() ; ++i)
	{
		aInterestOrderedPlanet.insert(&(pw.GetAllPlanets()[i]));
	}

#if 1
	InterestOrderedPlanet::iterator begin = aInterestOrderedPlanet.begin();
	InterestOrderedPlanet::iterator end = aInterestOrderedPlanet.end();
	InterestOrderedPlanet::iterator it;
#else
	InterestOrderedPlanet::reverse_iterator begin = aInterestOrderedPlanet.rbegin();
	InterestOrderedPlanet::reverse_iterator end = aInterestOrderedPlanet.rend();
	InterestOrderedPlanet::reverse_iterator it;
#endif

	for (it = begin ; it != end ; it++)
	{
		Planet* oAskingPlanet = *it;

		if (oAskingPlanet->Valuate() == 0.f && oAskingPlanet->GetInfluence() / pw.GetInfluenceSize() > 0.25f)
			continue;

		if (oAskingPlanet->GetOwner() == 0 
			&& oAskingPlanet->Valuate() < 1.f)
			continue;

		//if (oAskingPlanet->GetOwner() == 0 
		//	&& oAskingPlanet->GetInfluence() / pw.GetInfluenceSize() < 0.1f)
		//	continue;

		if (oAskingPlanet->GetOwner() == 0 
			&& oAskingPlanet->GetInfluence() < 0.f)
			continue;

		if (oAskingPlanet->GetOwner() == 2 && oAskingPlanet->Valuate() < 0.f)
			continue;

		oAskingPlanet->BroadcastDemand();
	}
	/*


		PositionOrderedPlanet::iterator begin2 = aPositionOrderedPlanet.begin();
		PositionOrderedPlanet::iterator end2 = aPositionOrderedPlanet.end();
		PositionOrderedPlanet::iterator it2;

		for (it2 = begin2 ; it2 != end2 ; it2++)
		{
			Planet& oOtherPlanet = *it2;



		}
	
	}
	*/




#if 0
	LOG("\n");
	LOG("Demand\n");
	for (uint i=0 ; i<pw.GetAllPlanets().size() ; ++i)
	{
		Planet& oPlanet = pw.GetAllPlanets()[i];
		oPlanet.CreateAndBroadcastDemand();
	}

	for (uint i=0 ; i<pw.GetAllPlanets().size() ; ++i)
	{
		Planet& oPlanet = pw.GetAllPlanets()[i];
		oPlanet.RespondToDemand();
	}

	for (uint i=0 ; i<pw.GetAllPlanets().size() ; ++i)
	{
		Planet& oPlanet = pw.GetAllPlanets()[i];
		oPlanet.ValidatePropal();
	}
#endif

#if 0

	LOG("\n");
	LOG("Evaluation :\n");

	const vector<Planet*>& AllMyPlanet = pw.GetOwnedPlanets();
	for (uint i=0 ; i<AllMyPlanet.size() ; ++i)
	{
		Planet& oPlanet = *AllMyPlanet[i];

		LOG("Planet %d : (%f %f %f)\n", oPlanet.GetPlanetID(), oPlanet.ValuateDanger(), oPlanet.GetOwnedInfluence(), oPlanet.GetEnemyInfluence());


		//uint16 iTurnCount;
		//uint16 iNewOwner;
		if (oPlanet.ValuateDanger() > 1.f)
		{
			LOG("  IN DANGER ! \n");
			continue;
		}

		uint16 iBestId = (uint16)-1;
		float fBestPlanet = 0;

		for (uint j=0 ; j<pw.GetAllPlanets().size() ; ++j)
		{
			const Planet& oOtherPlanet = pw.GetAllPlanets()[j];
			
			//if (oOtherPlanet.GetPlanetID() == oPlanet.GetPlanetID())
			//	continue;

			float fCurrentValue = oOtherPlanet.ValuateFor(oPlanet);

			if (fCurrentValue < 0.1f)
				continue;

			if (iBestId == (uint16)-1 || fCurrentValue > fBestPlanet)
			{
				iBestId = oOtherPlanet.GetPlanetID();
				fBestPlanet = fCurrentValue;
			}
		}

		if (iBestId != (uint16)-1 && iBestId != oPlanet.GetPlanetID())
		{

			const Planet& oPlanetTarget = pw.GetPlanet(iBestId);

			int iDist = pw.GetDistance(iBestId, oPlanet.GetPlanetID());

			uint16 iTargetCount = 0;

			iTargetCount = oPlanetTarget.GetShipsNeeded(iDist);

			uint16 iShipCount = min(oPlanet.GetShipsCapacity(), iTargetCount); // -1 pour ne pas se retrouver a 0
			if (iShipCount > 0)
				pw.CreateFleet((uint16)1, iShipCount, oPlanet.GetPlanetID(), iBestId, (sint16)0);

			/*
			while(iShipCount > 0)
			{
				uint16 iFleetID = pw.CreateFleet((uint16)1, iShipCount, oPlanet.GetPlanetID(), iBestId, (sint16)0);

				if (oPlanet.IsLosingOwner(0, iTurnCount, iNewOwner) == false)
					break;

				iShipCount -= (oPlanet.GetShipsCount(iTurnCount) + 1);
				pw.RemoveFleet(iFleetID);
			}
			*/

			LOG("\tChoose %d  Send %d\n", iBestId, iShipCount);
		}
	}

	PlanetWars::FleetMap::const_iterator begin = pw.GetAllFleets().begin();
	PlanetWars::FleetMap::const_iterator end = pw.GetAllFleets().end();
	PlanetWars::FleetMap::const_iterator it;

	for (it = begin ; it != end ; )
	{
		const Fleet& oFleet = it->second;
		 ++it;

		if (oFleet.GetStartTurn() != 0)
			continue;

		const Planet& oDestPlanet = pw.GetPlanet(oFleet.GetDestinationPlanet());

		if (oDestPlanet.GetOwner() == 1)
			continue;
		
		uint16 iTurn;
		uint16 iOwner;
		if (oDestPlanet.IsLosingOwner(0, iTurn, iOwner))
		{
			if (iTurn > (uint)oFleet.GetFinishTurn())
			{
				pw.EditFleet(oFleet.GetID(), oFleet.GetShipsCount(), iTurn - oFleet.GetTotalTripLength());
			}
		}
		else if (oDestPlanet.GetOwner() == 0)
		{
			pw.RemoveFleet(oFleet.GetID());
		}
	}
#endif

	LOG("\n");
#ifdef MYDEBUG
	PrintPlanet("Post Order :");
#endif

	LOG("\n");
}

#ifdef MYDEBUG
void PrintPlanet(char* sTitle)
{
	const int iTitleSize = 62;
	const int iColumnSize = 9;

	if (strlen(sTitle) > iTitleSize)
		sTitle[iTitleSize] = 0;

	const uint iNextTurnLog = (g_bVisualDebug ? 15 : MAX_TURN);
	
	LOG("%-*s", iTitleSize, sTitle);
	for (uint j=0 ; j<iNextTurnLog ; ++j)
	{
		LOG("%-*d", iColumnSize, pw.GetTurnNumber() + j);
	}
	LOG("\n");

	const vector<Planet>& AllPlanet = pw.GetAllPlanets();
	for (uint i=0 ; i<AllPlanet.size() ; ++i)
	{
		AllPlanet[i].Log(iNextTurnLog);
	}
}
#endif

