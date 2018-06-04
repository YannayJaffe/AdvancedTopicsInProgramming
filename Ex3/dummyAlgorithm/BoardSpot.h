//
// Created by yanna on 05/20/18.
//

#ifndef EX2_BOARDSPOT_H
#define EX2_BOARDSPOT_H

#include "PointImpl.h"

class BoardSpot
{
public:
    BoardSpot(const Point& location, int owner, char pieceType, char jokerRep = '#', bool assumedFlag = false) : location(location), owner(owner),
                                                                                                                 pieceType(pieceType),
                                                                                                                 jokerRep(jokerRep),
                                                                                                                 assumedFlag(assumedFlag)
    {}
    
    const Point& getLocation() const
    {
        return location;
    }
    
    int getOwner() const
    {
        return owner;
    }
    
    char getPieceType() const
    {
        return pieceType;
    }
    
    char getJokerRep() const
    {
        return jokerRep;
    }
    
    bool getAssumedFlag() const
    {
        return assumedFlag;
    }

private:
    
    const PointImpl location;
    const int owner;
    const char pieceType;
    const char jokerRep;
    const bool assumedFlag;
    
};


#endif //EX2_BOARDSPOT_H
