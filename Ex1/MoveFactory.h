#ifndef EX1_MOVEFACTORY_H
#define EX1_MOVEFACTORY_H

#include "GameMove.h"
#include <ifstream>
#include <string>
#include <vector>

class MoveFactory
{
public:
    MoveFactory(const std::string& fileName);
    
    bool anyMovesLeft() const;
    
    bool nextMoveParseable() const;
    
    GameMove getNext();

private:
    
    void clearSpaces();
    bool isInteger(const std::string& s) const;
    const std::string fileName;
    std::ifstream moveStream;
    std::string nextMove;
    std::vector<std::string> nextMoveTokens;
    
};


#endif //EX1_MOVEFACTORY_H
