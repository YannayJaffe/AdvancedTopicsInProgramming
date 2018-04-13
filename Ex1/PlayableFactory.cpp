#include "PlayableFactory.h"

PlayableFactory::PlayableFactory(const std::string& fileName) : fileName(fileName), stream()
{

}

bool PlayableFactory::init()
{
    try
    {
        stream.open(fileName);
    } catch (...)
    {
        return false;
    }
    return true;
}

PlayableFactory::~PlayableFactory()
{
    clear();
}

bool PlayableFactory::anyLeft() const
{
    return !stream.eof();
}

bool PlayableFactory::clear()
{
    if (stream.is_open())
    {
        try
        {
            stream.close();
        } catch (...)
        {
            return false;
        }
        
    }
    return true;
}

std::vector<std::string> PlayableFactory::splitToTokens(const std::string& line) const
{
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (!ss.eof())
    {
        std::getline(ss, token);
        if (token.length() > 0)
            tokens.push_back(std::move(token));
    }
    
    return tokens; // not returning using std::move in order to utilize RVO
}
