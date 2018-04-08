#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H

#include "GeneralDefinitions.h"
#include "GameBoard.h"
#include "GamePiece.h"
#include <istream>

class Player
{
public:
    Player(PlayerID id,GameBoard& board,std::istream& initialPositions,std::istream& moves);
    bool playerInit();//assume that bomb conflict (against not bomb) during init keeps the bomb
    bool isLost();
    bool playNextMove();//assume that bomb conflict during the match kills both pieces
private:
    
    bool isLegalInitCommand();
    bool isLegalMove(int fromX,int fromY,int toX,int toY);
    bool isLegalJokerMove();
    
    const PlayerID id;
    GameBoard& board;
    
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
    
    std::istream& initialPositions;
    std::istream& moves;
};


#endif //EX1_PLAYER_H
