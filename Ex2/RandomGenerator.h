//
// Created by yanna on 05/19/18.
//

#ifndef EX2_RANDOMGENERATOR_H
#define EX2_RANDOMGENERATOR_H

#include <cstdlib>
#include <ctime>

class RandomGenerator
{
public:
    RandomGenerator()
    {
        srand(static_cast<unsigned int>(time(nullptr)));
    }
    
    int getRange(int min, int max)
    {
        return rand() % (max + 1 - min) + min;
    }
};


#endif //EX2_RANDOMGENERATOR_H
