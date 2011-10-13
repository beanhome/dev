#include "Navigation.h"
#include "Square.h"
#include "World.h"
#include "StringUtils.h"

Navigation::Navigation(const Grid& oGrid)
	: m_oModelGrid(oGrid)
{
}

Navigation::~Navigation()
{}

