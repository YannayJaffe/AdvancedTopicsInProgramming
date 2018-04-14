
#ifndef EX1_PLAYABLE_H
#define EX1_PLAYABLE_H


#include <utility>
#include "GeneralDefinitions.h"
class Playable
{
public:
    virtual bool isJoker() const = 0;
    virtual const std::pair<int,int>& getNewLocation() const = 0;
    virtual PieceType getNewType() const = 0;
    virtual ~Playable() = default;
};




#endif //EX1_PLAYABLE_H
