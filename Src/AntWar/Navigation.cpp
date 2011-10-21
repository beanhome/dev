#include "Navigation.h"
#include "Square.h"
#include "World.h"
#include "StringUtils.h"

Navigation::Navigation()
{
}

Navigation::Navigation(const Grid& oGrid)
	: m_pModelGrid(&oGrid)
{
}

Navigation::~Navigation()
{}

void Navigation::Create(const Grid& oGrid)
{
	m_pModelGrid = &oGrid;
}
