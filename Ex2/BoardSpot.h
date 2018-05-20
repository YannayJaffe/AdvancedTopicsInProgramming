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
                                                                                                                 assumedFlag(assumedFlag),
                                                                                                                 pieceType(pieceType),
                                                                                                                 jokerRep(jokerRep)
    {}
    
    const Point& getLocation() const
    {
        return location;
    }
    
    const int getOwner() const
    {
        return owner;
    }
    
    const char getPieceType() const
    {
        return pieceType;
    }
    
    const char getJokerRep() const
    {
        return jokerRep;
    }
    
    const bool getAssumedFlag() const
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
