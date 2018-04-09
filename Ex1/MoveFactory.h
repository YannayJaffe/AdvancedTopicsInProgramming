#ifndef EX1_MOVEFACTORY_H
#define EX1_MOVEFACTORY_H

#include "GameMove.h"
#include <istream>
#include <string>
#include <vector>

class MoveFactory
{
public:
    MoveFactory(std::istream& moveStream);
    
    bool anyMovesLeft() const;
    
    bool nextMoveParseable() const;
    
    GameMove getNext();

private:
    
    void clearSpaces();
    bool isInteger(const std::string& s) const;
    std::istream& moveStream;
    std::string nextMove;
    std::vector<std::string> nextMoveTokens;
    
};


#endif //EX1_MOVEFACTORY_H
