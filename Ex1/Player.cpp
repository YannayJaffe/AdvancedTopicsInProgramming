#include "Player.h"

Player::Player(PlayerID id, GameBoardForPlayers& board, const std::string& playerBoard) : id(id), board(board), playerBoard(playerBoard)
{
    rCount = 0;
    pCount = 0;
    sCount = 0;
    bCount = 0;
    jCount = 0;
    fCount = 0;
    points = 0;
    movablePiecesCount = 0;
}

bool Player::initBoard()
{
    InitFactory initFactory(playerBoard);
    if (!initFactory.init())
    {// couldnt open board placement file
        
        std::cout << "Couldn't open board setup file for " << toString() << std::endl;
        
    }
    return false;
}

std::string Player::toString()
{
    if (id == PlayerID::Player1)
        return "player 1";
    else if (id == PlayerID::Player2)
        return "player 2";
    else
        return "unknown player";
}
