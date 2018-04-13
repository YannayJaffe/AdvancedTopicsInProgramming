#include "GameMove.h"

GameMove::GameMove() : GameMove(-1, -1, -1, -1, false, -1, -1, PieceType::Joker)
{

}

GameMove::GameMove(int prevX, int prevY, int newX, int newY) : GameMove(prevX, prevY, newX, newY, false, -1, -1, PieceType::Joker)
{

}

GameMove::GameMove(int prevX, int prevY, int newX, int newY, bool jokerMove, int jokerX, int jokerY, PieceType newType) : prevLocation(prevX, prevY),
                                                                                                                          newLocation(newX, newY),
                                                                                                                          jokerMove(jokerMove),
                                                                                                                          jokerLocation(jokerX,
                                                                                                                                        jokerY),
                                                                                                                          newType(newType)
{

}

GameMove::GameMove(GameMove&& other) : prevLocation(std::move(const_cast<std::pair<int, int>&&>(other.prevLocation))),
                                       newLocation(std::move(const_cast<std::pair<int, int>&&>(other.newLocation))),
                                       jokerMove(other.jokerMove), jokerLocation(std::move(const_cast<std::pair<int,int>&&>(other.jokerLocation))),
                                       newType(other.newType)
{

}

bool GameMove::isJoker() const
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

const std::pair<int, int>& GameMove::getJokerLocation() const
{
    return jokerLocation;
}

