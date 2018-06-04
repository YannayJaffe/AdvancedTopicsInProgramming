//
// Created by yanna on 05/16/18.
//

#ifndef EX2_JOKERCHANGEIMPL_H
#define EX2_JOKERCHANGEIMPL_H

#include "JokerChange.h"
#include "PointImpl.h"

class JokerChangeImpl : public JokerChange
{
public:
    
    JokerChangeImpl(const Point& position, char newRep) : position(position), newRep(newRep)
    {}
    
    const Point& getJokerChangePosition() const override
    {
        return position;
    }
    
    char getJokerNewRep() const override
    {
        return newRep;
    }
    
    ~JokerChangeImpl() override
    {
    
    }

private:
    const PointImpl position;
    const char newRep;
};

#endif //EX2_JOKERCHANGEIMPL_H
