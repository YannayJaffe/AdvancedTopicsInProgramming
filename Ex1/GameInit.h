
#ifndef EX1_GAMEINIT_H
#define EX1_GAMEINIT_H

#include "Playable.h"
class GameInit : public Playable
{
public:
    GameInit(int x, int y, bool jokerMove, PieceType newType);
    
    GameInit();
    
    GameInit(GameInit&& other);
    
    bool isJoker() const override;
    
    const PieceType getNewType() const override;
    
    const std::pair<int, int>& getNewLocation() const override;
    

private:
    const std::pair<int, int> newLocation;
    const bool jokerMove;
    const PieceType newType;

};


#endif //EX1_GAMEINIT_H
