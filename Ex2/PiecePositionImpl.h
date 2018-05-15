//
// Created by yanna on 05/15/18.
//

#ifndef EX2_PIECEPOSITIONIMPL_H
#define EX2_PIECEPOSITIONIMPL_H

#include "PiecePosition.h"
#include "Point.h"
#include "PointImpl.h"

class PiecePositionImpl : public PiecePosition
{
public:
    PiecePositionImpl(const Point& point, char pieceChar, char jokerRep):point(point),pieceChar(pieceChar),jokerRep(jokerRep){}
    
    const Point& getPosition() const override {return point;}
    
    char getPiece() const override {return pieceChar;}
    
    char getJokerRep() const override {return jokerRep;}
    
    ~PiecePositionImpl() override = default;

private:
    const PointImpl point;
    const char pieceChar;
    const char jokerRep;
};


#endif //EX2_PIECEPOSITIONIMPL_H
