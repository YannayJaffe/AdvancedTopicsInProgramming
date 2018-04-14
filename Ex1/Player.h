#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H

#include "GeneralDefinitions.h"
#include "GameBoardForPlayers.h"
#include "GamePiece.h"
#include "GameMove.h"
#include "MoveFactory.h"
#include "InitFactory.h"
#include <iostream>

class Player
{
public:
    Player(PlayerID id, GameBoardForPlayers& board, const std::string& playerBoard);
    
    bool initBoard();
    
    bool canMove();
    
    bool anyFlagsLeft();
    
    bool playNextMove();
    
    std::string toString();

private:
    const PlayerID id;
    GameBoardForPlayers& board;
    const std::string playerBoard;
    
    
    static const int R = 2; // total Rocks
    static const int P = 5; // total Papers
    static const int S = 1; // total Scissors
    static const int B = 2; // total Bombs
    static const int J = 2; // total Jokers
    static const int F = 1; // total Flags
    
    int rCount;
    int pCount;
    int sCount;
    int bCount;
    int jCount;
    int fCount;
    int movablePiecesCount;
    int points;
    
    
    
};


#endif //EX1_PLAYER_H
