#include "GameMove.h"

GameMove::GameMove(int prevX, int prevY, int newX, int newY) : GameMove(prevX, prevY, newX, newY, false, PieceType::Joker)
{

}

GameMove::GameMove(int prevX, int prevY, int newX, int newY, bool jokerMove, PieceType newType) : prevLocation(prevX, prevY), newLocation(newX, newY),
                                                                                                  jokerMove(jokerMove), newType(newType)
{

}

bool GameMove::isJokerMove() const
{
    return jokerMove;
}

const std::pair<int, int>& GameMove::getPrevLocation() const
{
    return prevLocation;
}

const std::pair<int, int>& GameMove::getNewLocation() const
{
    return newLocation;
}

const PieceType GameMove::getNewType() const
{
    return newType;
}
