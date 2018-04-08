#include "Player.h"

Player::Player(PlayerID id, GameBoard& board, std::istream& initialPositions, std::istream& moves) : id(id), board(board),
                                                                                                     initialPositions(initialPositions), moves(moves)
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
