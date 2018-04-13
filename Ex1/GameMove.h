#ifndef EX1_GAMEMOVE_H
#define EX1_GAMEMOVE_H


#include <utility>
#include "GeneralDefinitions.h"

class GameMove
{
public:
    GameMove(int prevX, int prevY, int newX, int newY, bool jokerMove, int jokerX, int jokerY, PieceType newType);
    
    GameMove(int prevX, int prevY, int newX, int newY);
    
    GameMove();
    
    GameMove(GameMove&& other);
    
    bool isJokerMove() const;
    
    const std::pair<int, int>& getPrevLocation() const;
    
    const PieceType getNewType() const;
    
    const std::pair<int, int>& getNewLocation() const;
    
    const std::pair<int, int>& getJokerLocation() const;

private:
    const std::pair<int, int> prevLocation;
    const std::pair<int, int> newLocation;
    const std::pair<int,int> jokerLocation;
    const bool jokerMove;
    const PieceType newType;
    
};


#endif //EX1_GAMEMOVE_H
