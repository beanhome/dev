#include "Grid.h"
#include "Utils.h"

#include "Square.h"


void Grid::NewTurn()
{
	for (uint x=0 ; x<GetWidth() ; ++x)
	{
		for (uint y=0 ; y<GetHeight() ; ++y)
		{
			GetCase(x, y).NewTurn();
		}
	}
}


#ifdef MYDEBUG
void Grid::Draw(int iTurn, int i, int j) const
{
	for (uint x=0 ; x<GetWidth() ; ++x)
	{
		for (uint y=0 ; y<GetHeight(); ++y)
		{
			GetCase(x, y).Draw(x, y, GetWidth(), GetHeight(), iTurn, (x==i && j==y));
		}
	}
}
#endif


