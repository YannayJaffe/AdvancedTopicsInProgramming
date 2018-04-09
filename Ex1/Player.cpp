#include "Player.h"

Player::Player(PlayerID id, GameBoardForPlayers& board) : id(id), board(board)
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
