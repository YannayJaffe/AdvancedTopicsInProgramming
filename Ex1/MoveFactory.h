#ifndef EX1_MOVEFACTORY_H
#define EX1_MOVEFACTORY_H

#include "GameMove.h"
#include <string>
#include <vector>
#include <fstream>

class MoveFactory
{
public:
    MoveFactory(const std::string& fileName);
    
    ~MoveFactory();
    
    bool anyMovesLeft() const;
    
    bool init();
    
    bool clear();
    
    GameMove getNext(bool& isValidMove);

private:
    
    std::vector<std::string> splitToTokens(const std::string& line) const;
    
    bool isLegalTokens(const std::vector<std::string>& tokens);
    
    void resetMove();
    
    const std::string fileName;
    mutable std::ifstream moveStream;
    
    int prevX, prevY, newX, newY;
    bool jokerMove;
    int jokerX, jokerY;
    PieceType newType;
    
};


#endif //EX1_MOVEFACTORY_H
