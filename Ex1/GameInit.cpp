//
// Created by yanna on 04/13/18.
//

#include "GameInit.h"

GameInit::GameInit(int x, int y, bool jokerMove, PieceType newType) : newLocation(x, y), jokerMove(jokerMove), newType(newType)
{

}

GameInit::GameInit() : GameInit(-1, -1, false, PieceType::Joker)
{

}

GameInit::GameInit(GameInit&& other) : newLocation(std::move(const_cast<std::pair<int, int>&&>(other.newLocation))), jokerMove(other.jokerMove),
                                       newType(other.newType)
{

}

bool GameInit::isJoker() const
{
    return jokerMove;
}

const PieceType GameInit::getNewType() const
{
    return newType;
}

const std::pair<int, int>& GameInit::getNewLocation() const
{
    return newLocation;
}



