//
// Created by yanna on 05/19/18.
//

#ifndef EX2_RANDOMGENERATOR_H
#define EX2_RANDOMGENERATOR_H

#include <stdlib.h>
#include <time.h>

class RandomGenerator
{
public:
    RandomGenerator()
    {
        srand(time(NULL));
    }
    
    int getRange(int min, int max)
    {
        return rand() % (max + 1 - min) + min;
    }
};


#endif //EX2_RANDOMGENERATOR_H
