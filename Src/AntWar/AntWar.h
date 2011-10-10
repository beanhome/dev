#ifndef ANTWAR_H
#define ANTWAR_H

#include "World.h"

struct AntWar
{
    World m_oWorld;

    AntWar();

    void PlayGame();    //plays a single game of Ants

    void MakeMoves();   //makes moves for a single turn
	
	void ExecMove(const Vector2 &loc, EDirection direction);
    void EndTurn();
};

#endif //ANTWAR_H
