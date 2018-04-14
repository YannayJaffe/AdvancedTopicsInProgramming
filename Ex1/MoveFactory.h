#ifndef EX1_MOVEFACTORY_H
#define EX1_MOVEFACTORY_H

#include "GameMove.h"
#include "PlayableFactory.h"
#include <string>
#include <memory>
#include <vector>
#include <fstream>

class MoveFactory : public PlayableFactory
{
public:
    MoveFactory(const std::string& fileName);
 
private:
    bool isLegalTokens(const std::vector<std::string>& tokens) override;

    std::unique_ptr<Playable> get() override;
    
    void resetMove() override;
    
    int prevX, prevY, newX, newY;
    bool jokerMove;
    int jokerX, jokerY;
    PieceType newType;
    
};


#endif //EX1_MOVEFACTORY_H
