#ifndef EX1_GAMEBOARDFORPLAYERS_H
#define EX1_GAMEBOARDFORPLAYERS_H

#include "GameBoard.h"

class Player;

class GameBoardForPlayers : public GameBoard
{
public:
    // give players access to GameBoards protected methods. only players should modify the GameBoard
    friend class Player;
    //GameBoardForPlayers();
};


#endif //EX1_GAMEBOARDFORPLAYERS_H
