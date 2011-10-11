#ifndef GRID_H
#define GRID_H

#include "Utils.h"
#include "GridBase.h"

class Square;

class Grid : public GridBase<Square>
{
	public:
		void NewTurn();

#ifdef MYDEBUG
		void Draw(int iTurn, int i, int j) const;
#endif
};

#endif //GRID_H
