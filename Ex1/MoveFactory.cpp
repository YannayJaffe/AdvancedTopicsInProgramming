

#include "MoveFactory.h"
#include <regex>

MoveFactory::MoveFactory(const std::string& fileName) : fileName(fileName), moveStream()
{


}

bool MoveFactory::init()
{
    try
    {
        moveStream.open(fileName);
    } catch (...)
    {
        return false;
    }
    return true;
}

bool MoveFactory::clear()
{
    if (moveStream.is_open())
    {
        try
        {
            moveStream.close();
        } catch (...)
        {
            return false;
        }
        
    }
    return true;
}

GameMove MoveFactory::getNext(bool& isValidMove) const
{
    if (!anyMovesLeft())
    {
        isValidMove = false;
        return GameMove();
    }
    std::string newLine;
    std::getline(moveStream, newLine);
    std::vector<std::string> tokens = splitToTokens(newLine);
    return GameMove();
}

std::vector<std::string> MoveFactory::splitToTokens(const std::string& line) const
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

bool MoveFactory::isLegalTokens(const std::vector<std::string>& tokens)
{
    switch (tokens.size())
    {
        case 4:
            try
            {
                prevX = std::stoi(tokens[0]);
                prevY = std::stoi(tokens[1]);
                newX = std::stoi(tokens[2]);
                newY = std::stoi(tokens[3]);
                jokerMove = false;
                jokerX = -1;
                jokerY = -1;
                newType = PieceType::Joker;
            } catch (const std::invalid_argument& ia)
            {
                resetMove();
                return false;
            }
            break;
        case 8:
            try
            {
                prevX = std::stoi(tokens[0]);
                prevY = std::stoi(tokens[1]);
                newX = std::stoi(tokens[2]);
                newY = std::stoi(tokens[3]);
                if (tokens[4] != "J:")
                {
                    resetMove();
                    return false;
                }
                else
                {
                    jokerMove = true;
                }
                jokerX = std::stoi(tokens[5]);
                jokerY = std::stoi(tokens[6]);
                if (tokens[7] == "R")
                    newType = PieceType::Rock;
                else if (tokens[7] == "P")
                    newType = PieceType::Paper;
                else if (tokens[7] == "S")
                    newType = PieceType::Scissors;
                else if (tokens[7] == "B")
                    newType = PieceType::Bomb;
                else
                {
                    resetMove();
                    return false;
                }
                
            } catch (const std::invalid_argument& ia)
            {
                resetMove();
                return false;
            }
            break;
        default:
            return false;
    }
    return true;
}

bool MoveFactory::anyMovesLeft() const
{
    return !moveStream.eof();
}

void MoveFactory::resetMove()
{
    prevX = -1;
    prevY = -1;
    newX = -1;
    newY = -1;
    jokerMove = false;
    jokerX = -1;
    jokerY = -1;
    newType = PieceType::Joker;
}

