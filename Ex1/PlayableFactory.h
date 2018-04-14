#ifndef EX1_PLAYABLEFACTORY_H
#define EX1_PLAYABLEFACTORY_H

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include "Playable.h"

class PlayableFactory
{
public:
    PlayableFactory(const std::string& fileName);
    
    virtual ~PlayableFactory();
    
    virtual bool anyLeft() const;
    
    virtual bool init();
    
    
    virtual std::unique_ptr<Playable> getNext(bool& isValidPlay, bool& isEmptyLine);

protected:
    virtual bool clear();
    
    virtual std::vector<std::string> splitToTokens(const std::string& line) const;
    
    virtual bool isLegalTokens(const std::vector<std::string>& tokens) = 0;
    
    virtual std::unique_ptr<Playable> get() = 0;
    
    virtual void resetMove() = 0;
    
    const std::string fileName;
    mutable std::ifstream stream;
    
};


#endif //EX1_PLAYABLEFACTORY_H
