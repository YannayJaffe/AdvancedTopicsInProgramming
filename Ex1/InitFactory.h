#ifndef EX1_INITFACTORY_H
#define EX1_INITFACTORY_H

#include "PlayableFactory.h"
#include "GeneralDefinitions.h"

class InitFactory : public PlayableFactory
{
public:
    InitFactory(const std::string& fileName);
    
    std::unique_ptr<Playable> getNext(bool& isValidPlay) override;

private:
    void resetMove() override;
    
    bool isLegalTokens(const std::vector<std::string>& tokens) override;

private:
    int x, y;
    bool joker;
    PieceType type;
};


#endif //EX1_INITFACTORY_H
