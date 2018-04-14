#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H

#include "GeneralDefinitions.h"
#include "GameBoardForPlayers.h"
#include "GameMove.h"
#include "MoveFactory.h"
#include "InitFactory.h"
#include <memory>
#include <iostream>

class Player
{
public:
    Player(PlayerID id, GameBoardForPlayers& board, const std::string& playerBoard, const std::string& playerMoves);
    
    int initBoard(); // returns 0 if succeeded or line number if got error
    
    bool initMoves();
    
    bool hasMoreMoves() const;
    
    bool playMove();
    
    bool hasMovablePieces() const;
    
    bool hasMoreFlags() const;
    
    std::string toString();
    
    enum class PlayerState
    {
        UNINIT, INIT_OPENED, INIT_DONE, MOVE_OPENED
        
    };
    
    PlayerState getState() const;
    
    const std::string& getLastErrorString() const;
    
    const PlayerID getId() const;
    
    void addPoint();
    
    int getPoints() const;
    
    int getLineCnt() const;

private:
    
    
    bool hasRemainingPieces(PieceType pieceType) const;
    
    const PlayerID id;
    GameBoardForPlayers& board;
    const std::string playerBoard;
    const std::string playerMoves;
    PlayerState state;
    
    static const int R = 2; // total Rocks
    static const int P = 5; // total Papers
    static const int S = 1; // total Scissors
    static const int B = 2; // total Bombs
    static const int J = 2; // total Jokers
    static const int F = 1; // total Flags
    
    int rCountInFile;
    int pCountInFile;
    int sCountInFile;
    int bCountInFile;
    int jCountInFile;
    int fCountInFile;
    
    int movablePiecesCount;
    int points;
    std::string lastErrorString;
    
    MoveFactory moveFactory;
    int lineCnt;
    
};


#endif //EX1_PLAYER_H
