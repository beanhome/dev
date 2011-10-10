
#ifndef PLANET_WARS_H_
#define PLANET_WARS_H_

#include <string>
#include <vector>
#include <map>
#include <cmath>

#include "Utils.h"

#include "Planet.h"
#include "Fleet.h"
#include "Request.h"

#ifdef MYDEBUG
#include "Graphic.h"
#endif

#define IMGDIR "../../Data/PlanetWar/Images/"

extern class PlanetWars pw;


// This is a utility class that parses strings.
class StringUtil
{
	public:
		// Tokenizes a string s into tokens. Tokens are delimited by any of the
		// characters in delimiters. Blank tokens are omitted.
		static void Tokenize(const string& s, const string& delimiters, vector<string>& tokens);

		// A more convenient way of calling the Tokenize() method.
		static vector<string> Tokenize(const string& s, const string& delimiters = string(" "));
};


// Stores information about one planet. There is one instance of this class
// for each planet on the map.
class PlanetWars
{
	public:
		PlanetWars();
		~PlanetWars();

		void NewTurn(uint16 iTurnNumber, const string& s, bool bInverted = false);

		uint GetTurnNumber() const { return m_iTurnNumber; }

		// Returns the planet with the given planet_id. There are NumPlanets()
		// planets. They are numbered starting at 0.
		const Planet& GetPlanet(int planet_id) const;
		Planet& GetPlanet(int planet_id);

		// Returns the fleet with the given fleet_id. Fleets are numbered starting
		// with 0. There are GetFleetsCount() fleets. fleet_id's are not consistent from
		// one turn to the next.
		const Fleet& GetFleet(int fleet_id) const;

		// Returns a list of all the planets.
		vector<Planet>& GetAllPlanets() { return m_aPlanets; }

		// Return a list of all the planets owned by the current player. By
		// convention, the current player is always player number 1.
		const vector<Planet*>& GetOwnedPlanets() const { return m_aOwnedPlanets; }

		// Return a list of all neutral planets.
		const vector<Planet*>& GetNeutralPlanets() const { return m_aNeutralPlanets; }

		// Return a list of all the planets owned by rival players. This excludes
		// planets owned by the current player, as well as neutral planets.
		const vector<Planet*>& GetEnemyPlanets() const { return m_aEnemyPlanets; }

		// Return a list of all the planets that are not owned by the current
		// player. This includes all enemy planets and neutral planets.
		const vector<Planet*>& GetNotOwnedPlanets() const { return m_aNotOwnedPlanets; }

		// Return a list of all the fleets.
		const FleetMap& GetAllFleets() const { return m_aFleets; }

		// Returns the distance between two planets, rounded up to the next highest
		// integer. This is the number of discrete time steps it takes to get between
		// the two planets.
		uint16 GetDistance(int source_planet, int destination_planet) const;

		// Sends an order to the game engine. The order is to send num_ships ships
		// from source_planet to destination_planet. The order must be valid, or
		// else your bot will get kicked and lose the game. For example, you must own
		// source_planet, and you can't send more ships than you actually have on
		// that planet.
		void IssueOrder(int source_planet, int destination_planet, int num_ships) const;

		// Sends a message to the game engine letting it know that you're done
		// issuing orders for now.
		void FinishTurn() const;

		void ExecuteOrders();

		// Returns true if the named player owns at least one planet or fleet.
		// Otherwise, the player is deemed to be dead and false is returned.
		bool IsAlive(uint player_id) const;

		int GetTotalShipsCount() const { return m_iTotalOwnedShipCount + m_iTotalEnemyShipCount; }
		int GetTotalPlanetCount() const { return m_iTotalOwnedPlanetCount + m_iTotalEnemyPlanetCount; }
		int GetTotalOwnedPlanetCount() const { return m_iTotalOwnedPlanetCount; }
		int GetTotalEnemyPlanetCount() const { return m_iTotalEnemyPlanetCount; }
		int GetTotalOwnedShipsCount() const { return m_iTotalEnemyShipCount; }
		int GetTotalEnemyShipsCount() const { return m_iTotalEnemyPlanetCount; }


		void AddPlanet(uint iId, uint iOwner, uint iShipCount, uint iGrowthRate, float fX, float fY);
		void AddFleet(uint16 iOwner, uint16 iShipCount, uint16 iSourcePlanet, uint16 iDestinationPlanet, uint16 iTotalTripLength, uint16 iTurnsRemaining);
		uint16 CreateFleet(uint16 iOwner, uint16 ishipCount, uint16 iSourcePlanet, uint16 iDestinationPlanet, sint16 iStartTurn);
		void RemoveFleet(uint16 id);
		void EditFleet(uint16 id, uint16 iShipCount, sint16 iStartTurn);

		Request& GetRequest(uint16 id);
		const Request& GetRequest(uint16 id) const;
		void AddRequest(uint16 iSrcPlanet, uint16 iShipNeeded, uint16 iTurn);
		void RemoveRequest(uint16 iID);

		void RegisterInfluence(float fInfluence);
		void RemoveInfluence(const Planet& oPlanetToRemove);
		void ApplyInfluence(const Planet& oPlanetToApply);
		float GetInfluenceSize() const { return max(fabs(m_fMaxInfluence), fabs(m_fMinInfluence)); }
		float GetInfluenceMin() const { return m_fMinInfluence; }
		float GetInfluenceMax() const { return m_fMaxInfluence; }

		float GetWidth() const { return m_fWidth; }
		float GetHeight() const { return m_fHeight; }
		float GetSize() const { return m_fSize; }

#ifdef MYDEBUG
		void ConvertSpace(float x_in, float y_in, sint16& x_out, sint16& y_out) const;
		void Draw(bool bPostCompute = false, uint iPlanetSelect = (uint)-1);
		uint16 DrawLoop(bool bPostCompute);
#endif

	private:
		// Parses a game state from a string. On success, returns 1. On failure,
		// returns 0.
		int ParseGameState(const string& s, bool bInverted = false);

		void ComputeData();

		void Clear();

		void SetTurnNumber(uint16 iTurnNumber) { m_iTurnNumber = iTurnNumber; }

	private:
		uint16 m_iTurnNumber;
		uint16 m_iFleetCounter;
		uint16 m_iRequestCounter;

		vector<Planet> m_aPlanets;

		FleetMap m_aFleets;

		vector<Planet*> m_aOwnedPlanets;
		vector<Planet*> m_aNotOwnedPlanets;
		vector<Planet*> m_aEnemyPlanets;
		vector<Planet*> m_aNeutralPlanets;

		vector<Fleet*> m_aOwnedFleets;
		vector<Fleet*> m_aEnemyFleets;

		RequestMap m_aRequest;

		uint m_iTotalOwnedPlanetCount;
		uint m_iTotalEnemyPlanetCount;
		uint m_iTotalOwnedShipCount;
		uint m_iTotalEnemyShipCount;
		uint m_iTotalOwnedGrowthRate;
		uint m_iTotalEnemyGrowthRate;

		float m_fWidth;
		float m_fHeight;
		float m_fSize;

		float m_fMaxInfluence;
		float m_fMinInfluence;

#ifdef MYDEBUG
		GraphicImage* m_pBG;
		bool m_bKeyDown;
		uint m_iKeyDownTime;
		uint m_iRepeatDelay;
		uint m_iFirstRepeatDelay;
		uint m_iNextRepeatDelay;
#endif
};

#endif
