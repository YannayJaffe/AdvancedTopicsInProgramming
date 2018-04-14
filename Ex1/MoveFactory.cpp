

#include "MoveFactory.h"

MoveFactory::MoveFactory(const std::string& fileName) : PlayableFactory(fileName)
{


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
                } else
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
            resetMove();
            return false;
    }
    return true;
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

std::unique_ptr<Playable> MoveFactory::get()
{
    return std::make_unique<GameMove>(prevX, prevY, newX, newY, jokerMove, jokerX, jokerY, newType);
}

