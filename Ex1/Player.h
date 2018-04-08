#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H

#include "GeneralDefinitions.h"
#include "GameBoard.h"
#include "GamePiece.h"

class Player
{
public:
private:
    const PlayerID id;
    GameBoard& board;
    
    static const int R = 2; // total Rocks
    static const int P = 5; // total Papers
    static const int S = 1; // total Scissors
    static const int B = 2; // total Bombs
    static const int J = 2; // total Jokers
    static const int F = 1; // total Flags
};


#endif //EX1_PLAYER_H
