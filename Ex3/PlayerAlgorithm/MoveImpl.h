//
// Created by yanna on 05/16/18.
//

#ifndef EX2_MOVEIMPL_H
#define EX2_MOVEIMPL_H


#include "Move.h"
#include "PointImpl.h"

class MoveImpl : public Move
{
public:
    MoveImpl(const Point& from, const Point& to) : from(from), to(to)
    {}
    
    const Point& getFrom() const override
    {
        return from;
    }
    
    const Point& getTo() const override
    {
        return to;
    }
    
    ~MoveImpl() override
    {
    
    }

private:
   const PointImpl from;
   const PointImpl to;
    
    
};


#endif //EX2_MOVEIMPL_H
