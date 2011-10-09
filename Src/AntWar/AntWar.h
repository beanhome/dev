#ifndef ANTWAR_H
#define ANTWAR_H

#include "World.h"

struct AntWar
{
    World m_oWorld;

    AntWar();

    void playGame();    //plays a single game of Ants

    void MakeMoves();   //makes moves for a single turn
    void EndTurn();     //indicates to the engine that it has made its moves
};

#endif //ANTWAR_H
