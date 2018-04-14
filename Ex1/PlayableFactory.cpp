#include "PlayableFactory.h"

PlayableFactory::PlayableFactory(const std::string& fileName) : fileName(fileName), stream()
{

}

bool PlayableFactory::init()
{
    stream.exceptions(std::ifstream::failbit);
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
        std::getline(ss, token, ' ');
        if (token.length() > 0)
            tokens.push_back(std::move(token));
    }
    
    return tokens; // not returning using std::move in order to utilize RVO
}

std::unique_ptr<Playable> PlayableFactory::getNext(bool& isValidPlay, bool& isEmptyLine)
{
    std::string newLine;
    try
    {
        std::getline(stream, newLine);
    } catch (const std::ios::failure& f)
    {
        //read last line
        isEmptyLine = true;
    }
    isEmptyLine = newLine.empty();
    if (isEmptyLine)
    {
        isValidPlay = true;
        return nullptr;
    }
    
    std::vector<std::string> tokens = splitToTokens(newLine);
    if (!isLegalTokens(tokens))
    {
        isValidPlay = false;
        return nullptr;
    }
    isValidPlay = true;
    return get();
}
