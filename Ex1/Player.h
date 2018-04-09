#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H

#include "GeneralDefinitions.h"
#include "GameBoardForPlayers.h"
#include "GamePiece.h"
#include "GameMove.h"
class Player
{
public:
    Player(PlayerID id, GameBoardForPlayers& board);
    bool playerInit();//assume that bomb conflict (against not bomb) during init keeps the bomb
    bool isLost();
    bool playMove(const GameMove& gameMove);//assume that bomb conflict during the match kills both pieces
private:
    
    bool isLegalInitCommand();
    bool isLegalMove(const GameMove& gameMove);
    
    const PlayerID id;
    GameBoardForPlayers& board;
    
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
