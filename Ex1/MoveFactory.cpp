

#include "MoveFactory.h"
#include <regex>

MoveFactory::MoveFactory(std::istream& moveStream) : moveStream(moveStream), nextMove(""), nextMoveTokens()
{
    if (anyMovesLeft())
    {
        nextMove = moveStream.getline();
        clearSpaces();
    }
    
}

bool MoveFactory::anyMovesLeft() const
{
    if (moveStream.eof() && nextMoveTokens.empty())
        return false;
    return true;
}

void MoveFactory::clearSpaces()
{
    nextMoveTokens.clear();
    std::size_t start = 0;
    std::size_t end = 0;
    while (end != std::string::npos && start <= nextMove.length())
    {
        end = nextMove.find(' ', start);
        nextMoveTokens.push_back(nextMove.substr(start, (end == std::string::npos) ? std::string::npos : end - start));
        start = end + 1;
    }
    
    
}

bool MoveFactory::nextMoveParseable() const
{
    if (nextMoveTokens.size() == 4)
    {
    
    } else if (nextMoveTokens.size() == 8)
    {
    
    } else
        return false;
}

bool MoveFactory::isInteger(const std::string& s) const
{
    return std::regex_match(s,std::regex("^(\\-|\\+)?[0-9]+"));
}

               