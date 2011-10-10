
#include "Square.h"

Square::Square()
	: m_bIsVisible(false)
	, m_bIsWater(false)
	, m_bIsFood(false)
	, m_iAntPlayer(-1)
	, m_iHillPlayer(-1)
{}

void Square::Init(const char* line, const char* sNext)
{

	switch (line[0])
	{
	case 'w': // water
		m_bIsWater = true;
		break;

	case 'f': // food
		m_bIsFood = true;
		break;

	case 'h': // hill
		ASSERT(sNext != NULL);
		m_iHillPlayer = atoi(sNext);
		break;

	case 'a': // live ant
		ASSERT(sNext != NULL);
		m_iAntPlayer = atoi(sNext);
		break;

	case 'd': // dead ant
		ASSERT(sNext != NULL);
		m_aDeadAnts.push_back(atoi(sNext));
		break;
	}
}

void Square::NewTurn()
{
	m_bIsFood = false;
	m_iHillPlayer = -1;
	m_iAntPlayer = -1;
}



