#include <cmath>
#include <cstdlib>

#include "Utils.h"
#include "Planet.h"
#include "Fleet.h"
#include "PlanetWars.h"

const float Planet::s_fInfluenceCoeff = 20.f;

const float Planet::s_fNeutralValueCoeff = 10.f;
const float Planet::s_fNeutralUnderNMEAttackCoeff = 1.f;
const float Planet::s_fNeutralInfluenceThreshold = 0.8f;
const float Planet::s_fNeutralInfluenceCoeff = 0.25f;

const float Planet::s_fOwnedLosingCoeff = 1.f;
const float Planet::s_fOwnedUnderNMEAttackCoeff = 1.2f;
const float Planet::s_fOwnedPositionCoeff = 1.f;
const float Planet::s_fOwnedGrowthCoeff = 1.f;

const float Planet::s_fEnemyValueCoeff = 7.f;
const float Planet::s_fEnemyUnderAttackCoeff = 1.f;
const float Planet::s_fEnemyInfluenceThreshold = 0.8f;
const float Planet::s_fEnemyInfluenceCoeff = 0.3f;


Planet::Planet(int planet_id, int owner, int num_ships, int growth_rate, float x, float y)
	: m_iPlanetId((uint16)planet_id)
	, m_iGrowthRate((uint16)growth_rate)
	, m_fX(x)
	, m_fY(y)
	, m_iOwner((uint16)owner)
	, m_iShipsCount((sint16)num_ships)
	, m_iShipsCapacity((sint16)num_ships)
	, m_iNextOwner((uint16)owner)
	, m_iLoseOwnerTurn((uint16)0)
	, m_fOwnedInfluence(0.f)
	, m_fEnemyInfluence(0.f)
	, m_fInfluence(0.f)
	//, m_iDemandCounter(0)
	//, m_iPropalCounter(0)
{
	m_aNextTurn[0].m_iOwner = (uint16)m_iOwner;
	m_aNextTurn[0].m_iShipCount = (sint16)m_iShipsCount;

#ifdef MYDEBUG
	m_pImage = NULL; //GraphicLoadBMP("");
#endif
}

Planet::~Planet()
{
#ifdef MYDEBUG
	if (m_pImage != NULL)
		ge.FreeImage(m_pImage);
#endif
}

void Planet::RegisterPlanet(const Planet* pPlanet)
{
	uint16 iDist = GetDistance(*this, *pPlanet);

	m_aPlanets.insert(DistanceOrderedPlanetPair(iDist, pPlanet));
}



uint16 Planet::GetOwner(uint iTurn) const
{
	ASSERT(iTurn < MAX_TURN);
	return m_aNextTurn[iTurn].m_iOwner;
}


uint16 Planet::GetShipsCount(uint iTurn, uint iTesterOwner) const
{
	ASSERT(iTurn < MAX_TURN);
	sint32 iShipCount = m_aNextTurn[iTurn].m_iShipCount;
	
	if (iTurn > 0
	 && GetOwner(iTurn-1) == 0
	 && GetOwner(iTurn) != 0
	 && GetOwner(iTurn) != iTesterOwner)
	{
		const NextTurn& oNextTurn = m_aNextTurn[iTurn];

		set<uint16>::const_iterator begin = oNextTurn.m_aFleets.begin();
		set<uint16>::const_iterator end = oNextTurn.m_aFleets.end();
		set<uint16>::const_iterator it;

		for (it = begin ; it != end ; ++it)
		{
			const Fleet& oFleet = pw.GetFleet(*it);
			if ((uint)oFleet.GetFinishTurn() == iTurn
			 && oFleet.GetDestinationPlanet() == GetPlanetID()
			 && oFleet.GetOwner() == GetOwner(iTurn))
			{
				iShipCount += oFleet.GetShipsCount();
			}
		}
	}

	return (uint16)iShipCount;
}

/*
sint32 Planet::GetPotentialShipsCount(uint iTurn, uint16 iInitialShipCount) const
{
	sint32 iShipCount = iInitialShipCount;

	const NextTurn& oTurn = GetNextTurn(iTurn);

	for (uint i=0 ; i<oTurn.m_aPlanets.size() ; ++i)
	{
		const Planet& oOtherPlanet = *oTurn.m_aPlanets[i];
		switch (oOtherPlanet.GetOwner())
		{
			case 0:
				break;

			case 1:
				iShipCount += oOtherPlanet.GetRealShipsCount();
				break;

			case 2:
				iShipCount -= oOtherPlanet.GetRealShipsCount();
				break;
		}
	}

	return iShipCount;
}
*/


void Planet::AddFleet(const Fleet& oFleet)
{
	if (oFleet.GetSourcePlanet() == GetPlanetID())
	{
		if (oFleet.GetStartTurn() >= 0)
		{
			ASSERT(oFleet.GetStartTurn() < MAX_TURN);
			m_aNextTurn[oFleet.GetStartTurn()].m_aFleets.insert(oFleet.GetID());
		}
	}
	else
	{
		CHECK(oFleet.GetDestinationPlanet() == GetPlanetID(), "Error : bad Fleet\n");

		if (oFleet.GetFinishTurn() >= 0)
		{
			ASSERT(oFleet.GetFinishTurn() < MAX_TURN);
			m_aNextTurn[oFleet.GetFinishTurn()].m_aFleets.insert(oFleet.GetID());
		}
	}
}

void Planet::RemoveFleet(const Fleet& oFleet)
{
	if (oFleet.GetSourcePlanet() == GetPlanetID())
	{
		if (oFleet.GetStartTurn() >= 0)
		{
			ASSERT(oFleet.GetStartTurn() < MAX_TURN);
			m_aNextTurn[oFleet.GetStartTurn()].m_aFleets.erase(oFleet.GetID());
		}
	}
	else
	{
		CHECK(oFleet.GetDestinationPlanet() == GetPlanetID(), "Error : bad Fleet\n");

		if (oFleet.GetFinishTurn() >= 0)
		{
			ASSERT(oFleet.GetFinishTurn() < MAX_TURN);
			m_aNextTurn[oFleet.GetFinishTurn()].m_aFleets.erase(oFleet.GetID());
		}
	}
}

void Planet::Compute()
{
	m_iLoseOwnerTurn = 0;

	for (uint16 i=0 ; i<MAX_TURN ; ++i)
	{
		NextTurn& oNextTurn = m_aNextTurn[i];

		if (i == 0)
		{
			oNextTurn.m_iOwner = m_iOwner;
			oNextTurn.m_iShipCount = m_iShipsCount;
			oNextTurn.m_iShipGrowth[0] = 0;
			oNextTurn.m_iShipGrowth[1] = 0;
			oNextTurn.m_iShipGrowth[2] = 0;
			m_iShipsCapacity = m_iShipsCount;
		}
		else
		{
			NextTurn& oPrevTurn = m_aNextTurn[i-1];
			oNextTurn.m_iOwner = oPrevTurn.m_iOwner;
			oNextTurn.m_iShipCount = oPrevTurn.m_iShipCount;

			if (oNextTurn.m_iOwner > 0)
			{
				oNextTurn.m_iShipCount += GetGrowthRate();
			}
		}

		sint16 iShipCount[3] = {0,0,0};
		
		set<uint16>::const_iterator begin = oNextTurn.m_aFleets.begin();
		set<uint16>::const_iterator end = oNextTurn.m_aFleets.end();
		set<uint16>::const_iterator it;

		for (it = begin ; it != end ; ++it)
		{
			const Fleet& oFleet = pw.GetFleet(*it);

			if (oFleet.GetSourcePlanet() == GetPlanetID())
			{
				iShipCount[oFleet.GetOwner()] -= oFleet.GetShipsCount();
			}
			else
			{
				CHECK(oFleet.GetDestinationPlanet() == GetPlanetID(), "Error : Bad Planet\n");

				iShipCount[oFleet.GetOwner()] += oFleet.GetShipsCount();
			}
		}

		switch (oNextTurn.m_iOwner)
		{
			case 0:
				if (iShipCount[1] > oNextTurn.m_iShipCount || iShipCount[2] > oNextTurn.m_iShipCount)
				{
					uint16 j = (iShipCount[1] > iShipCount[2] ? 1 : 2);

					oNextTurn.m_iOwner = j;
					oNextTurn.m_iShipCount = iShipCount[j] - oNextTurn.m_iShipCount;
				}
				else
				{
					oNextTurn.m_iShipCount -= max(iShipCount[1], iShipCount[2]);
				}
				break;

			default:
				for (uint16 j=1 ; j<3 ; ++j)
				{
					oNextTurn.m_iShipCount += (iShipCount[j] * (j == oNextTurn.m_iOwner ? 1 : -1));
				}
				break;
		}

		
		if (oNextTurn.m_iShipCount < 0)
		{
			oNextTurn.m_iOwner = 3 - oNextTurn.m_iOwner;
			oNextTurn.m_iShipCount = -oNextTurn.m_iShipCount;
		}

		if (oNextTurn.m_iOwner == 1)
		{
			m_iShipsCapacity = min(oNextTurn.m_iShipCount, m_iShipsCapacity);
		}
		else
		{
			m_iShipsCapacity = 0;
		}

		if (i>0)
		{
			NextTurn& oPrevTurn = m_aNextTurn[i-1];
			
			for (uint j=0 ; j<3 ; ++j)
				oNextTurn.m_iShipGrowth[j] = oPrevTurn.m_iShipGrowth[j] + oNextTurn.m_iShipCount * (oNextTurn.m_iOwner == j ? 1 : -1) - oPrevTurn.m_iShipCount * (oPrevTurn.m_iOwner == j ? 1 : -1);
		}

		if (i>0
		 && m_aNextTurn[i].m_iOwner != m_aNextTurn[i-1].m_iOwner
		 && m_iLoseOwnerTurn == 0)
		{
			m_iLoseOwnerTurn = i;
			m_iNextOwner = oNextTurn.m_iOwner;
		}
	}


	//float fLastGrowthRate = GetGrowth(LAST_TURN, 1);

	m_iBestTurn = 0;
	for (uint16 i=0 ; i<MAX_TURN ; ++i)
	{
		NextTurn& oNextTurn = m_aNextTurn[i];

		sint16 iGrowthNeeded = max<sint16>(sint16(i * m_iGrowthRate) - oNextTurn.m_iShipGrowth[1], 0);
		uint16 iOwnedNeeded = GetShipsCount(i) + 1;

		switch (oNextTurn.m_iOwner)
		{
			case 0:
			case 2:
				oNextTurn.m_iShipNeededMin = iOwnedNeeded;
				oNextTurn.m_iShipNeededMax = max<sint16>(iGrowthNeeded, iOwnedNeeded);
				break;

			case 1:
				oNextTurn.m_iShipNeededMin = 0;
				oNextTurn.m_iShipNeededMax = iGrowthNeeded;
				break;

			default:
				break;
		}

		if (oNextTurn.m_iShipNeededMin < m_aNextTurn[m_iBestTurn].m_iShipNeededMin)
		{
			m_iBestTurn = i;
		}
	}
}

float Planet::GetInfluenceOn(const Planet& oOtherPlanet) const
{
	int iDist = GetDistance(*this, oOtherPlanet);
	float fInfluence = GetGrowthRate() * GetShipsCount() / (float)(iDist * iDist);
	// TODO : intégrer la perte d'owner ?

	return fInfluence;
}


void Planet::ComputeInfluence()
{
	m_fOwnedInfluence = 0.f;
	m_fEnemyInfluence = 0.f;
	uint16 iDistAverage = 0;
	float fInfluence;

	for (uint i=0 ; i<pw.GetAllPlanets().size() ; ++i)
	{
		const Planet& oOtherPlanet = pw.GetAllPlanets()[i];

		if (oOtherPlanet.GetPlanetID() == GetPlanetID())
			continue;

		iDistAverage += GetDistance(*this, oOtherPlanet);

		fInfluence = oOtherPlanet.GetInfluenceOn(*this);

		switch (oOtherPlanet.GetOwner())
		{
			case 0:
				continue;
				break;

			case 1:
				m_fOwnedInfluence += fInfluence;
				break;

			case 2:
				m_fEnemyInfluence += fInfluence;
				break;
		}
	}

	iDistAverage /= (uint16)pw.GetAllPlanets().size()-1;
	fInfluence = GetGrowthRate() * GetShipsCount() / (float)(iDistAverage * iDistAverage);
	switch (GetOwner())
	{
		case 1:		m_fOwnedInfluence += fInfluence;	break;
		case 2:		m_fEnemyInfluence += fInfluence;	break;
		default:	break;
	}

	m_fOwnedInfluence *= (pw.GetTotalOwnedPlanetCount() > 0 ? s_fInfluenceCoeff / (float)(pw.GetTotalOwnedPlanetCount()) : 0.f);
	m_fEnemyInfluence *= (pw.GetTotalEnemyPlanetCount() > 0 ? s_fInfluenceCoeff / (float)(pw.GetTotalEnemyPlanetCount()) : 0.f);


	m_fInfluence = (m_fOwnedInfluence > 0.f ? (m_fEnemyInfluence > 0.f ? log(m_fOwnedInfluence / m_fEnemyInfluence) : m_fOwnedInfluence) : -m_fEnemyInfluence);
	//m_fInfluence = m_fEnemyInfluence > 0.f ? m_fOwnedInfluence / m_fEnemyInfluence : m_fOwnedInfluence * 2.f;

	pw.RegisterInfluence(m_fInfluence);
}



/*
void Planet::AddShips(int amount)
{
	LOG("Add Ship\n");
	m_iShipsCount += amount;
}
*/

void Planet::RemoveRealShips(sint16 amount)
{
	m_iShipsCount -= amount;
}

void Planet::RemoveShips(sint16 amount)
{
	//m_iShipsCount -= amount;
	m_aNextTurn[0].m_iShipCount -= amount;
}

sint16 Planet::GetShipsNeeded(uint iDist) const
{
	sint16 iMaxNeeded;
	return GetShipsNeeded(iDist, iMaxNeeded);
}

sint16 Planet::GetShipsNeeded(uint iDist, sint16& iMaxNeeded) const
{
	iMaxNeeded = m_aNextTurn[iDist].m_iShipNeededMax;
	return m_aNextTurn[iDist].m_iShipNeededMin;

	/*
	sint16 iGrowthNeeded = max<sint16>((sint16)((float)iDist * ((float)GetGrowthRate() - GetGrowth(iDist, 1))), 0);
	uint16 iOwnedNeeded = GetShipsCount(iDist) + 1;

	uint16 iLosingTurn, iNewOwner;
	switch (GetOwner(iDist))
	{
		case 0:
		case 2:
			//return GetShipsCount(iDist) + 1;
			iMaxNeeded = max<sint16>(iGrowthNeeded, iOwnedNeeded);
			return iOwnedNeeded;

		case 1:
			if (IsLosingOwner((sint16)iDist, iLosingTurn, iNewOwner))
			{
				//return GetShipsCount(iLosingTurn) + 1;

				iGrowthNeeded = max<sint16>((sint16)((float)iLosingTurn * ((float)GetGrowthRate() - GetGrowth(iLosingTurn, 1))), 0);
				iOwnedNeeded = GetShipsCount(iLosingTurn) + 1;

				iMaxNeeded = max<sint16>(iGrowthNeeded, iOwnedNeeded);
				return iOwnedNeeded;
			}
			else
			{
				//sint16 iPos = (sint16)((1.f - (GetInfluence() - pw.GetInfluenceMin()) / (pw.GetInfluenceMax() - pw.GetInfluenceMin())) * 10.f);
				iMaxNeeded = iGrowthNeeded;// + iPos;
				return iMaxNeeded;
			}

		default:
			return 0;
	}
	*/
}

sint16 Planet::GetShipsCapacityFor(const Planet& oOtherPlanet) const
{
	uint16 iDist = GetDistance(*this, oOtherPlanet);

	//if (oOtherPlanet.GetGrowthRate() >= GetGrowthRate())
	//	return min(GetShipsCapacity(), oOtherPlanet.GetShipsNeeded(iDist));

	uint16 iEndDist;

	switch (oOtherPlanet.GetOwner(iDist))
	{
		case 0:		iEndDist = iDist * 2;		break;
		case 1:		iEndDist = iDist;			break;
		case 2:		iEndDist = iDist * 2;		break;
		default:	iEndDist = (uint16)pw.GetSize();	break;
	}

	DistanceOrderedPlanetMap::const_iterator begin = m_aPlanets.begin();
	DistanceOrderedPlanetMap::const_iterator end = m_aPlanets.upper_bound(iEndDist);
	DistanceOrderedPlanetMap::const_iterator it;

	sint16 iOwnedShips = 0; //GetShipsCount();
	sint16 iEnemyShips = 0;
	for (it = begin ; it != end ; ++it)
	{
		const Planet& oPlanet = *(it->second);

		switch (oPlanet.GetOwner())
		{
			case 1:		iOwnedShips += oPlanet.GetShipsCount();	break;
			case 2:		iEnemyShips += oPlanet.GetShipsCount();	break;
			default:	break;
		}
	}

	/*
	switch (oOtherPlanet.GetOwner(iDist))
	{
		case 0:
		{
			iOwnedShips -= oOtherPlanet.GetShipsCount();
			break;
		}

		case 1:
		{
			break;
		}

		case 2:
		{
			iOwnedShips -= oOtherPlanet.GetShipsCount();
			iEnemyShips -= oOtherPlanet.GetShipsCount();
			break;
		}

		default:
			return 0;
	}
	*/

	return max<sint16>(0, GetShipsCapacity() + min<sint16>(0, iOwnedShips - iEnemyShips));
}


bool Planet::IsLosingOwner(sint16 iStartTurn) const
{
	uint16 iLosingTurn;
	uint16 iOwner;

	return IsLosingOwner(iStartTurn, iLosingTurn, iOwner);
}

bool Planet::IsLosingOwner(sint16 iStartTurn, uint16& iLosingTurn, uint16& iOwner) const
{
	if (m_iLoseOwnerTurn == 0)
	{
		return false;
	}

	if (iStartTurn+1 <= m_iLoseOwnerTurn)
	{
		iLosingTurn = m_iLoseOwnerTurn;
		iOwner = m_iNextOwner;
		return (iLosingTurn > 0);
	}

	for (uint16 i=iStartTurn+1 ; i<MAX_TURN ; ++i)
	{
		if (m_aNextTurn[i].m_iOwner != m_aNextTurn[i-1].m_iOwner)
		{
			iLosingTurn = i;
			iOwner = m_aNextTurn[i].m_iOwner;
			return true;
		}
	}

	return false;
}

bool Planet::IsUnderAttack(uint16 iOwner, uint16& iTurn, uint16& iShipcount) const
{
	iTurn = 1;
	iShipcount = 1;

	for (uint16 i=1 ; i<MAX_TURN ; ++i)
	{
		const NextTurn& oNextTurn = m_aNextTurn[i];

		set<uint16>::const_iterator begin = oNextTurn.m_aFleets.begin();
		set<uint16>::const_iterator end = oNextTurn.m_aFleets.end();
		set<uint16>::const_iterator it;

		for (it = begin ; it != end ; ++it)
		{
			const Fleet& oFleet = pw.GetFleet(*it);
			if (oFleet.GetOwner() == iOwner)
			{
				iTurn = oFleet.GetTurnsRemaining();
				iShipcount = oFleet.GetShipsCount();
				return true;
			}
		}
	}

	return false;
}

uint16 Planet::GetDistance(const Planet& SrcPlanet, const Planet& DstPlanet)
{
	float dx = SrcPlanet.GetX() - DstPlanet.GetX();
	float dy = SrcPlanet.GetY() - DstPlanet.GetY();
	return (uint16)ceil(sqrt(dx * dx + dy * dy));
}

float Planet::GetGrowth(uint iTurn, uint iOwner) const
{
	ASSERT(iTurn < MAX_TURN);

	if (iTurn == 0)
		return 0.f;

	//if (IsLosingOwner() == false)
	//{
	//	return (float)((GetShipsCount(iTurn-1) - GetShipsCount(0)) * (iOwner == GetOwner() ? 1 : -1)) / (float)iTurn;
	//}

	return (float)m_aNextTurn[iTurn].m_iShipGrowth[iOwner] / (float)iTurn;

	/*
	if (IsLosingOwner() == false)
	{
		return (float)((GetShipsCount(iTurn-1) - GetShipsCount(0)) * (iOwner == GetOwner() ? 1 : -1)) / (float)iTurn;
	}
	else
	{
		int iCount = 0;
		for (uint16 i=0 ; i<iTurn ; ++i)
		{
			iCount += m_aNextTurn[i].m_iShipGrowth[iOwner];
		}

		return (float)iCount / (float)iTurn;
	}
	*/
}


float Planet::ValuateDanger(float* /*pval1*/, float* /*pval2*/, float* /*pval3*/) const
{
	/*
	float val1 = 0.f;
	float val2 = 0.f;
	float val3 = 0.f;

	val1 = (float)GetGrowthRate() / (GetShipsCount() > 0 ? (float)GetShipsCount() : 0.5f);
	val2 = exp(-GetGrowth(LAST_TURN, 1)) * s_fOwnedGrowthCoeff;
	val3 = m_fEnemyInfluence * s_fOwnedPositionCoeff;

	if (pval1 != NULL) *pval1 = val1;
	if (pval2 != NULL) *pval2 = val2;
	if (pval3 != NULL) *pval3 = val3;

	return val1 * (val2 + val3);
	*/

	float fGrowthDanger = max(0.f, 1.f - (GetGrowth(LAST_TURN, 1) / GetGrowthRate()));
	float fPosDanger = max(0.f, -m_fInfluence);

	return fGrowthDanger + fPosDanger;
}


float Planet::Valuate() const
{
	float val, val1, val2, val3;

	const float fCoeff = 3.7f;

	switch (GetOwner())
	{
		case 0:
			val1 = (float)m_iGrowthRate;
			val2 = m_fInfluence / pw.GetInfluenceSize() * fCoeff;
			val3 = 0.8f;
			val = (val1 + val2) * val3;
			break;

		case 1:
			val1 = (float)m_iGrowthRate;
			val2 = -m_fInfluence / pw.GetInfluenceSize() * fCoeff;
			val3 = ValuateDanger();
			val = (val1 + val2) * val3;
			break;

		case 2:
			val1 = (float)m_iGrowthRate;
			val2 = m_fInfluence / pw.GetInfluenceSize() * fCoeff;
			val3 = 0.9f;
			val = (val1 + val2) * val3;
			break;

		default:
			val = 0.f;
			break;
	}

	return val;
}

float Planet::ValuateFor(const Planet& oPlanet, float* pval1, float* pval2, float* pval3) const
{
	float val = 0.f;
	float val1 = 0.f;
	float val2 = 0.f;
	float val3 = 0.f;
	//float fInfluenceComp = 0.f;

	//uint16 iTurn, iShipCount;//, iOwner;

	uint iDist = Planet::GetDistance(*this, oPlanet);
	//uint iShipDiff = max(GetShipsCount(iDist) - oPlanet.GetShipsCount(), 1);
	//uint16 iVirtualShipCount = GetShipsCount(iDist, 1);
	//float fShipRatio = (float)oPlanet.GetShipsCount() / (iVirtualShipCount > 0 ? (float)iVirtualShipCount : 0.5f);


	if (GetOwner(iDist) == 0)
	{
		/*
		//val1 = (float)GetGrowthRate() / (float)(iDist*iDist) / (float)iShipDiff * s_fNeutralValueCoeff;
		val1 = (float)GetGrowthRate() / (float)(iDist*iDist) * fShipRatio * s_fNeutralValueCoeff;
		val2 = (IsUnderAttack(2, iTurn, iShipCount) && iTurn < iDist ? 1.f : 0.f) * s_fNeutralUnderNMEAttackCoeff;
		val3 = m_fInfluence * s_fNeutralInfluenceCoeff;
		val = val1 + val2 + val3;
		*/
		//LOG("\t %2d ValuateFor %2d [Neutral] (%2d) : %7.4f (%7.4f %7.4f %7.4f) %s\n", GetPlanetID(), oPlanet.GetPlanetID(), iDist, val, val1, val2, val3, (GetPlanetID() == oPlanet.GetPlanetID() ? "self" : ""));
		val1 = (float)m_iGrowthRate;
		val2 = m_fInfluence;
		val3 = 0.8f;
		val = (val1 + val2) * val3;

	}
	else if (GetOwner() == 1 || GetOwner(iDist) == 1)
	{
		val1 = (float)m_iGrowthRate;
		val2 = -m_fInfluence;
		val3 = ValuateDanger(pval1, pval2, pval3);
		val = (val1 + val2) * val3;

		//LOG("\t %2d ValuateFor %2d [Owned] (%2d)  : %7.4f %s\n", GetPlanetID(), oPlanet.GetPlanetID(), iDist, val, (GetPlanetID() == oPlanet.GetPlanetID() ? "self" : ""));
	}
	else if (IsLosingOwner((sint16)iDist) == false)
	{
		/*
		//val1 = (float)GetGrowthRate() / (float)(iDist*iDist) / (float)iShipDiff * s_fEnemyValueCoeff;
		val1 = (float)GetGrowthRate() / (float)(iDist*iDist) * fShipRatio * s_fEnemyValueCoeff;
		//val2 = (IsUnderAttack(1, iTurn, iShipCount) ? 1.f : 0.f) / (float)iTurn * (float)iShipCount / (GetShipsCount(iTurn) > 0 ? (float)GetShipsCount(iTurn) : 0.5f) * s_fEnemyUnderAttackCoeff;
		//fInfluenceComp = (m_fOwnedInfluence > 0.f ? (1.f - abs(1.f - (m_fEnemyInfluence / m_fOwnedInfluence))) : 0.f);
		//val3 = (fInfluenceComp > s_fEnemyInfluenceThreshold ? (fInfluenceComp - s_fEnemyInfluenceThreshold) / (1.f - s_fEnemyInfluenceThreshold) : 0.f) * s_fEnemyInfluenceCoeff;
		val3 = m_fInfluence * s_fEnemyInfluenceCoeff;
		val = val1 + val2 + val3;
		val2 = fShipRatio;
		*/

		val1 = (float)m_iGrowthRate;
		val2 = m_fInfluence;
		val3 = 0.9f;
		val = (val1 + val2) * val3;
	}

	if (pval1 != NULL) *pval1 = val1;
	if (pval2 != NULL) *pval2 = val2;
	if (pval3 != NULL) *pval3 = val3;

	return val;
}

bool FillID(uint16* tab, uint size, uint counter)
{
	for (uint i=0 ; i<size ; ++i)
	{
		if (tab[i] > 0)
		{
			if (i >= size-counter)
			{
				return false;
			}
			else if (counter > 0)
			{
				if (FillID(tab+i+1, size-(i+1), counter-1) == false)
				{
					if (i+1 >= size-counter)
					{
						return false;
					}

					tab[i]=0;
					tab[i+1]=1;
					for (uint j=i+2 ; j<size ; ++j)
						tab[j] = 0;
					return FillID(tab+i+2, size-(i+2), counter-1);
				}
				else
				{
					return true;
				}
			}
			else if (i+1 >= size-counter)
			{
				return false;
			}
			else
			{
				tab[i]=0;
				tab[i+1]=1;
				return true;
			}
		}
	}

	tab[0]=1;

	if (counter > 0 && size > 1)
		return FillID(tab+1, size-1, counter-1);

	return true;
}





void Planet::BroadcastDemand()
{
	PositionOrderedPlanet aPositionOrderedPlanet;

	for (uint i=0 ; i<pw.GetOwnedPlanets().size() ; ++i)
	{
		Planet& oOtherPlanet = *pw.GetOwnedPlanets()[i];
		uint16 iDist = GetDistance(oOtherPlanet, *this);

		ASSERT(oOtherPlanet.GetOwner() == 1);

		if (oOtherPlanet.GetPlanetID() == GetPlanetID())
			continue;

		//if (oOtherPlanet.ValuateDanger() > 0.f)
		//	continue;

		if (oOtherPlanet.GetShipsCapacityFor(*this) <=0)
			continue;

		if (GetShipsNeeded(iDist) <= 0)
			continue;


		// TODO Ponderer Influence
		float fValue = (pw.GetSize() - (float)iDist) + oOtherPlanet.GetInfluence();

		aPositionOrderedPlanet.insert(pair<float, Planet*>(fValue, &oOtherPlanet));
	}

	PositionOrderedPlanet::iterator begin = aPositionOrderedPlanet.begin();
	PositionOrderedPlanet::iterator end = aPositionOrderedPlanet.end();
	PositionOrderedPlanet::iterator it;

	uint size = aPositionOrderedPlanet.size();

	size = min<uint>(10, size);

	if (size > 0)
	{
		bool bMinSuccess = false;
		bool bMaxSuccess = false;
		float fMinShipRatio = 0.f;
		float fMaxShipRatio = 0.f;
		uint16 iMaxDist = 0;

		uint16* tab = new uint16[size];
		for (uint j=0 ; j<size ; ++j)
			tab[j] = 1;

		//if (TestSetOfPlanet(aPositionOrderedPlanet, tab, size, fMinShipRatio, fMaxShipRatio, iMaxDist)) // first Test full
		//{
		//	if (fMaxShipRatio < 1.f)
		//	{
		//		bMinSuccess = true;
		//		bMaxSuccess = false;
		//	}
		//	else
		//	{
				for (uint i=0 ; i<size && (!bMinSuccess || !bMaxSuccess) ; ++i)
				{
					for (uint j=0 ; j<size ; ++j)
						tab[j] = 0;
					while(FillID(tab, size, i))
					{
						fMinShipRatio = 0.f;
						fMaxShipRatio = 0.f;

						TestSetOfPlanet(aPositionOrderedPlanet, tab, size, fMinShipRatio, fMaxShipRatio, iMaxDist);

						bMinSuccess = (fMinShipRatio >= 1.f);
						bMaxSuccess = (fMaxShipRatio >= 1.f);

						if (bMinSuccess && bMaxSuccess)
						{
							break;
						}

						/*
						for (uint j=0 ; j<size ; ++j)
							LOG("%d ", tab[j]);
						LOG("\n");
						*/
					}
				}
		//	}
		//}

		/*
		if (!bSuccess && GetOwner() == 2)// && fShipRatio > 0.5f)
		{
			bSuccess = true;
			for (uint i=0 ; i<size ; ++i)
				tab[i] = 1;
		}
		*/

		if (bMinSuccess || bMaxSuccess || GetOwner() == 1)
		{
			uint j=0;
			for (it = begin ; it != end && j<size ; ++j, it++)
			{
				if (tab[j] > 0)
				{
					//Planet& oOtherPlanet = **it;
					Planet& oOtherPlanet = *(it->second);
					uint16 iDist = GetDistance(oOtherPlanet, *this);
					sint16 iMaxShipNeeded;
					/*sint16 iMinShipNeeded = */GetShipsNeeded(iMaxDist, iMaxShipNeeded);
					//sint16 iShipCapacity = oOtherPlanet.GetShipsCapacity(iDist, this);
					sint16 iShipCapacity = tab[j];

					//ASSERT(iShipCapacity > 0);
					if (iShipCapacity > 0)
					{
						uint16 iShipCount = min<uint16>(iShipCapacity, iMaxShipNeeded);
						if (GetOwner() == 0)
							pw.CreateFleet(1, iShipCount, oOtherPlanet.GetPlanetID(), GetPlanetID(), iMaxDist-iDist);
						else
							pw.CreateFleet(1, iShipCount, oOtherPlanet.GetPlanetID(), GetPlanetID(), 0);
					}
				}
			}
		}

		delete [] tab;
	}
}

bool Planet::TestSetOfPlanet(PositionOrderedPlanet& aPositionOrderedPlanet, uint16* tab, uint size, float& fMinShipRatio, float& fMaxShipRatio, uint16& iMaxDist)
{
	PositionOrderedPlanet::iterator begin = aPositionOrderedPlanet.begin();
	PositionOrderedPlanet::iterator end = aPositionOrderedPlanet.end();
	PositionOrderedPlanet::iterator it;

	iMaxDist = 0;
	uint j=0;
	for (it=begin ; it!=end && j<size ; ++j, it++)
	{
		if (tab[j] > 0)
		{
			Planet& oOtherPlanet = *(it->second);
			uint16 iDist = GetDistance(oOtherPlanet, *this);
			if (iDist > iMaxDist)
				iMaxDist = iDist;
		}
	}

	if (iMaxDist < m_iBestTurn)
		iMaxDist = m_iBestTurn;

	fMinShipRatio = 0.f;
	fMaxShipRatio = 0.f;
	j=0;
	for (it=begin ; it!=end && j<size ; ++j, it++)
	{
		if (tab[j] > 0)
		{
			//Planet& oOtherPlanet = **it;
			Planet& oOtherPlanet = *(it->second);
			//uint16 iDist = GetDistance(oOtherPlanet, *this);

			sint16 iShipCapacity = oOtherPlanet.GetShipsCapacityFor(*this);
			ASSERT(iShipCapacity > 0);
			sint16 iMaxShipNeeded;
			sint16 iMinShipNeeded = GetShipsNeeded(iMaxDist, iMaxShipNeeded);

			fMinShipRatio += (float)(iShipCapacity) / (float)iMinShipNeeded;
			fMaxShipRatio += (float)(iShipCapacity) / (float)iMaxShipNeeded;

			tab[j] = iShipCapacity;
		}
	}

	return (fMinShipRatio >= 1.f);
}


#if 0
void Planet::CreateAndBroadcastDemand()
{
	for (uint i=0 ; i<pw.GetAllPlanets().size() ; ++i)
	{
		Planet& oDemandPlanet = pw.GetAllPlanets()[i];
		if (oDemandPlanet.GetPlanetID() != GetPlanetID())
		{
			uint16 iDist = GetDistance(*this, oDemandPlanet);
			
			uint16 iLosingTurn = 0;
			uint16 iNewOwner;

			if (oDemandPlanet.GetOwner() == 1
			 || oDemandPlanet.IsLosingOwner(0, iLosingTurn, iNewOwner) && iNewOwner == 1)
			{
				iDist += iLosingTurn;
				iDist = min(iDist, (uint16)(LAST_TURN));

				sint16 iShipNeeded = GetShipsNeeded(iDist);

				if (iShipNeeded > 0)
				{
					Demand oDemand(m_iDemandCounter++, iShipNeeded, oDemandPlanet.GetPlanetID(), GetPlanetID());
					m_aDemandSend.insert(DemandSendPair(oDemand.GetID(), oDemand));

					oDemandPlanet.ReceiveDemand(oDemand);
				}
			}
		}
	}
}


void Planet::ReceiveDemand(const Demand& oDemand)
{
	const Planet& oAskingPlanet = pw.GetPlanet(oDemand.GetAskingPlanet());
	//uint16 iDist = GetDistance(*this, oAskingPlanet);
	float fValue = oAskingPlanet.ValuateFor(*this);
	m_aDemandReceive.insert(DemandReceivePair(fValue, oDemand));
}

void Planet::RespondToDemand()
{
	for (DemandReceiveMap::reverse_iterator it = m_aDemandReceive.rbegin() ; it != m_aDemandReceive.rend() ; it++)
	{
		if (m_iShipsCapacity > 0)
		{
			const Demand& oDemand = it->second;
			Planet& oAskingPlanet = pw.GetPlanet(oDemand.GetAskingPlanet());
			uint16 iShipSended = min<uint16>(m_iShipsCapacity, oDemand.GetShipsCount());
			Propal oPropal(m_iPropalCounter++, oDemand.GetID(), iShipSended, GetPlanetID(), oDemand.GetAskingPlanet());
			m_aPropalSend.insert(PropalSendPair(oPropal.GetID(), oPropal));
			oAskingPlanet.ReceivePropal(oPropal);
			m_iShipsCapacity -= iShipSended;
		}
	}

	m_aDemandReceive.clear();
}

void Planet::ReceivePropal(const Propal& oPropal)
{
	Planet& oPropalPlanet = pw.GetPlanet(oPropal.GetPropalPlanet());
	uint16 iDist = GetDistance(*this, oPropalPlanet);
	m_aPropalReceive.insert(PropalReceivePair(iDist, oPropal));
}

void Planet::ValidatePropal()
{
	PropalReceiveMap::iterator begin = m_aPropalReceive.begin();
	PropalReceiveMap::iterator end = m_aPropalReceive.end();
	PropalReceiveMap::iterator it;

	uint size = m_aPropalReceive.size();
	if (size > 0)
	{
		uint8* tab = new uint8[size];

		bool bSuccess = false;
		float fShipRatio = 0.f;
		for (uint i=0 ; i<size && !bSuccess ; ++i)
		{
			for (uint j=0 ; j<size ; ++j)
				tab[j] = 0;
			while(FillID(tab, size, i))
			{
				fShipRatio = 0.f;
				uint j=0;
				for (it=begin ; it!=end && j<size ; ++j, it++)
				{
					const Propal& oPropal = it->second;
					DemandSendMap::iterator itDemand = m_aDemandSend.find(oPropal.GetDemandID());
					const Demand& oDemand = itDemand->second;
					fShipRatio += (float)(oPropal.GetShipsCount() * tab[j]) / (float)oDemand.GetShipsCount();
				}

				if (fShipRatio >= 1.f)
				{
					bSuccess = true;
					break;
				}

				/*
				for (uint j=0 ; j<size ; ++j)
					LOG("%d ", tab[j]);
				LOG("\n");
				*/
			}
		}

		/*
		if (!bSuccess && GetOwner() == 2)// && fShipRatio > 0.5f)
		{
			bSuccess = true;
			for (uint i=0 ; i<size ; ++i)
				tab[i] = 1;
		}
		*/

		if (bSuccess)
		{
			float fShipRatio = 0.f;
			uint j=0;
			for (it = begin ; it != end && j<size ; ++j, it++)
			{
				Propal& oPropal = it->second;
				Planet& oPlanet = pw.GetPlanet(oPropal.GetPropalPlanet());

				if (tab[j] > 0)
				{
					DemandSendMap::iterator itDemand = m_aDemandSend.find(oPropal.GetDemandID());
					const Demand& oDemand = itDemand->second;

					float fPropalShipRatio = (float)oPropal.GetShipsCount() / (float)oDemand.GetShipsCount();
					if (fShipRatio + fPropalShipRatio > 1.f)
					{
						fPropalShipRatio = 1.f - fShipRatio;
						oPropal.SetShipCount(min<uint16>(oPropal.GetShipsCount(), (uint16)((float)oDemand.GetShipsCount() * fPropalShipRatio) + 1));
					}
					fShipRatio += fPropalShipRatio;

					oPlanet.AcceptPropal(oPropal);
				}

				oPlanet.DeletePropal(oPropal);
			}
		}

		delete [] tab;
	}


	m_aDemandSend.clear();
	m_aPropalReceive.clear();

}

void Planet::AcceptPropal(const Propal& oPropal)
{
	PropalSendMap::iterator it = m_aPropalSend.find(oPropal.GetID());
	pw.CreateFleet((uint16)1, oPropal.GetShipsCount(), GetPlanetID(), oPropal.GetDemandPlanet(), (sint16)0);
}

void Planet::DeletePropal(const Propal& oPropal)
{
	PropalSendMap::iterator it = m_aPropalSend.find(oPropal.GetID());
	m_aPropalSend.erase(it);
}
#endif




#ifdef MYDEBUG
void Planet::Log(uint iNextTurnLog) const
{
	LOG("Planet %2d : (%d) %7.3f %7.3f (%5.2f %5.2f %5.2f %5.2f)", GetPlanetID(), GetGrowthRate(), GetX(), GetY(), ValuateDanger(), m_fOwnedInfluence, m_fEnemyInfluence, m_fInfluence);
	for (uint j=0 ; j<iNextTurnLog ; ++j)
	{
		LOG("  | %d %3d", GetNextTurn(j).m_iOwner, GetNextTurn(j).m_iShipCount);
	}
	LOG("\n");
	//LOG("Message : %d %d %d %d\n", m_aDemandSend.size(), m_aDemandReceive.size(), m_aPropalSend.size(), m_aPropalReceive.size());
	//LOG("\n");

	for (uint j=0 ; j<MAX_TURN ; ++j)
	{
		const set<uint16>& aFleetsID = GetNextTurn(j).m_aFleets;

		set<uint16>::const_iterator begin = aFleetsID.begin();
		set<uint16>::const_iterator end = aFleetsID.end();
		set<uint16>::const_iterator it;

		for (it = begin ; it != end ; ++it)
		{
			LOG("\t ");
			pw.GetFleet(*it).Log();
		}
	}

}

float Planet::GetRadius(uint iGrowthRate)
{
	return (0.4f + (float)iGrowthRate * 0.12f);
}

float Planet::ConvertRadius(float fRadius)
{
	return fRadius * (float)gf_pw.GetWidth() / pw.GetWidth();
}

void GetOwnerColor(uint16 iOwner, uint8& r, uint8& g, uint8& b, uint8 coeff=8)
{
	coeff = min(8, coeff);

	switch(iOwner)
	{
		case 0:		r = 24*coeff-1;  g = 24*coeff-1;  b = 24*coeff-1;  break;
		case 1:		r = 32*coeff-1;  g = 4*coeff-1;   b = 4*coeff-1;   break;
		case 2:		r = 4*coeff-1;   g = 4*coeff-1;   b = 32*coeff-1;  break;
	}

	/*
	r = min(r, 255);
	g = min(g, 255);
	b = min(b, 255);
	*/
}

void Planet::Draw(uint iPlanetSelect) const
{
	sint16 x, y;
	pw.ConvertSpace(GetX(), GetY(), x, y);
	sint16 radius = (sint16)ConvertRadius(GetRadius(GetGrowthRate()));
	sint16 radius_p = (sint16)((float)radius*0.8f);

	uint8 r = 0;
	uint8 g = 0;
	uint8 b = 0;

	GetOwnerColor(GetOwner(), r, g, b, 7);
	gf_pw.DrawFillCircle(x, y, radius, r, g, b);
	gf_pw.DrawCircle(x, y, radius, 255, 255, 255);

	gf_pw.Print(x, y, 16, Center, 0, 0, 0, "%d", GetShipsCount());
	gf_pw.Print((x - radius_p), (y - radius_p), 12, Center, 0, 0, 0, "%d", GetPlanetID());

	/*
	float fOwnedInfl = m_fOwnedInfluence * 350.f / (float)(pw.GetTotalOwnedPlanetCount());
	float fEnemyInfl = m_fEnemyInfluence * 350.f / (float)(pw.GetTotalEnemyPlanetCount());
	gf_pw.Print(x, y-12, 10, Center, 220,220,220, "%6.3f",  fOwnedInfl / fEnemyInfl);
	gf_pw.Print(x, y+12, 10, Center, 220,220,220, "%6.3f",  m_fOwnedInfluence / m_fEnemyInfluence);
	*/

	float val = Valuate();
	GetOwnerColor(GetOwner(), r, g, b, 4);
	gf_pw.Print(x, y+12, 12, Center, r,g,b, "%6.3f", val);

	r = 64; g = 64; b = 64;
	if (m_fInfluence > 0.f)			{	r = 64; g = 0; b = 0;	}
	else if (m_fInfluence < 0.f)	{	r = 0;  g = 0; b = 64;	}
	gf_pw.Print(x, y+24, 12, Center, r,g,b, "%6.3f", m_fInfluence);



	float val1, val2, val3;
	float fDanger = ValuateDanger(&val1, &val2, &val3);
	sint16 xpos = x-radius;
	sint16 ypos = y+radius;
	
	if (iPlanetSelect < pw.GetAllPlanets().size() && pw.GetPlanet(iPlanetSelect).GetOwner() == 1)
	{
		uint iDist = GetDistance(*this, pw.GetPlanet(iPlanetSelect));
		gf_pw.Print((x + radius_p), (y - radius_p), 12, Center, 0, 0, 0, "%d", iDist);

		//r = 64; g = 64; b = 64;
		//if (m_fInfluence > 0.f)			{	r = 192; g = 64; b = 64;	}
		//else if (m_fInfluence < 0.f)	{	r = 64;  g = 64; b = 192;	}
		//gf_pw.Print(xpos, ypos, 10, LeftTop, r,g,b, "Infl : (%6.3f/%6.3f) %6.3f", m_fOwnedInfluence, m_fEnemyInfluence, m_fInfluence);
		//ypos += 10;

		//r = ((GetGrowth(iDist, 1) > 0.f) ? 192 : 64);
		//g = 64;
		//b = ((GetGrowth(iDist, 2) > 0.f) ? 192 : 64);
		//gf_pw.Print(xpos, ypos, 10, LeftTop, r,g,b, "Growth : %6.3f %6.3f %6.3f", GetGrowth(iDist, 0), GetGrowth(iDist, 1), GetGrowth(iDist, 2));
		//ypos += 10;

		//if (GetOwner(iDist) == 1)
		//{
		//	r = (fDanger > 1.f ? 192 : 10);
		//	gf_pw.Print(xpos, ypos, 10, LeftTop, r,10,10, "Danger : %6.3f", fDanger);
		//	ypos += 10;
		//}

		//gf_pw.Print(xpos, ypos, 10, LeftTop, r,g,b, "%6.3f %6.3f %6.3f", val1, val2, val3);
		//ypos += 10;
	}



	if (iPlanetSelect == GetPlanetID())
	{
		xpos = 10;
		ypos = 10;
		uint16 size = 12;
		
		GetOwnerColor(GetOwner(), r, g, b, 8);
		gf_dbg.Print(xpos, ypos, size, LeftTop, r, g, b, "Planet %d (%d)", GetPlanetID(), GetGrowthRate());
		ypos += size;
		gf_dbg.Print(xpos, ypos, 10, LeftTop, 32,32,32, "Ships Capacity : %d", m_iShipsCapacity);
		ypos += size;
		gf_dbg.Print(xpos, ypos, 10, LeftTop, 10,10,10, "Danger : %6.3f", fDanger);
		ypos += size;

		for (uint i=0 ; i<MAX_TURN && ypos < gf_dbg.GetHeight() ; ++i)
		{
			xpos = 10;

			uint16 iShipCount = GetShipsCount(i);

			GetOwnerColor(GetOwner(i), r, g, b, 8);
			gf_dbg.Print(xpos, ypos, size, LeftTop, r,g,b, "  %3d : [%3d]", i, iShipCount);
			xpos += 70;

			//GetOwnerColor(GetPotentialShipsCount(i, iShipCount) >= 0 ? 1 : 0, r, g, b, 8);
			//gf_dbg.Print(xpos, ypos, size, LeftTop, r,g,b, "  (%3d)", GetPotentialShipsCount(i, iShipCount));
			//xpos += 50;

			//GetOwnerColor(GetGrowth(i, 0) > 0.f ? 1 : 0, r, g, b, 8);
			//gf_dbg.Print(xpos, ypos, size, LeftTop, r,g,b, "  %+6.3f", GetGrowth(i, 0));
			//xpos += 50;

			GetOwnerColor(GetGrowth(i, 1) > 0.f ? 1 : 2, r, g, b, 8);
			gf_dbg.Print(xpos, ypos, size, LeftTop, r,g,b, "  %+6.3f", GetGrowth(i, 1));
			xpos += 50;

			//GetOwnerColor(GetGrowth(i, 2) > 0.f ? 2 : 1, r, g, b, 8);
			//gf_dbg.Print(xpos, ypos, size, LeftTop, r,g,b, "  %+6.3f", GetGrowth(i, 2));
			//xpos += 50;

			GetOwnerColor(GetOwner(i), r, g, b, 8);
			gf_dbg.Print(xpos, ypos, size, LeftTop, r,g,b, "  %4d %4d", m_aNextTurn[i].m_iShipNeededMin, m_aNextTurn[i].m_iShipNeededMax);
			xpos += 50;

			ypos += size;

			//gf_dbg.Print(xpos, ypos, size, LeftTop, r,g,b, "  %3d : [%3d]   Growth %+6.3f %+6.3f %+6.3f", i, GetShipsCount(i), GetGrowth(i, 0), GetGrowth(i, 1), GetGrowth(i, 2) );
			//
		}
	}
}
#endif
