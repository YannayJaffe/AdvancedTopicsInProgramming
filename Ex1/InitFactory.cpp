//
// Created by yanna on 04/13/18.
//

#include "InitFactory.h"

InitFactory::InitFactory(const std::string& fileName) : PlayableFactory(fileName)
{

}

void InitFactory::resetMove()
{
    x = -1;
    y = -1;
    joker = false;
    type = PieceType::Joker;
}

bool InitFactory::isLegalTokens(const std::vector<std::string>& tokens)
{
    std::string const* pieceChar = nullptr;
    switch (tokens.size())
    {
        case 3:
            try
            {
                pieceChar = &tokens[0];
                x = std::stoi(tokens[1]);
                y = std::stoi(tokens[2]);
                
            } catch (...)
            {
                resetMove();
                return false;
            }
            break;
        case 4:
            try
            {
                if (tokens[0] != "J")
                {
                    resetMove();
                    return false;
                }
                x = std::stoi(tokens[1]);
                y = std::stoi(tokens[2]);
                pieceChar = &tokens[3];
            } catch (...)
            {
                resetMove();
                return false;
            }
            break;
        default:
            resetMove();
            return false;
    }
    if (pieceChar != nullptr && *pieceChar == "R")
    {
        type = PieceType::Rock;
        return true;
    } else if (pieceChar != nullptr && *pieceChar == "P")
    {
        type = PieceType::Paper;
        return true;
    } else if (pieceChar != nullptr && *pieceChar == "S")
    {
        type = PieceType::Scissors;
        return true;
    } else if (pieceChar != nullptr && *pieceChar == "B")
    {
        type = PieceType::Bomb;
        return true;
    } else if (pieceChar != nullptr && *pieceChar == "F")
    {
        type = PieceType::Flag;
        return true;
    } else
    {
    resetMove();
    return false;
    }
}

std::unique_ptr<Playable> InitFactory::get()
{
    return std::make_unique<GameInit>(x,y,joker,type);
}
