#ifndef EX1_INITFACTORY_H
#define EX1_INITFACTORY_H

#include "PlayableFactory.h"
#include "GeneralDefinitions.h"
#include "GameInit.h"

class InitFactory : public PlayableFactory
{
public:
    InitFactory(const std::string& fileName);

private:
    void resetMove() override;
    
    bool isLegalTokens(const std::vector<std::string>& tokens) override;
    
    std::unique_ptr<Playable> get() override;
    
    int x, y;
    bool joker;
    PieceType type;
};


#endif //EX1_INITFACTORY_H
