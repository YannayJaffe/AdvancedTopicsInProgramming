//
// Created by yanna on 05/07/18.
//

#include "FilePlayerAlgorithm.h"

void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
    //treat this method as some kind of init to load positioning from relevant files
    // also load all moves from files and create moves vector
    playerId = player;
    initFileName = std::string("player") + std::to_string(playerId) + std::string(".rps_board");
    movesFileName = std::string("player") + std::to_string(playerId) + std::string(".rps_moves");
    moveCount = 0;
    fillInitialPositions(vectorToFill);
    fillMovesJokers();
    
}

void FilePlayerAlgorithm::notifyOnInitialBoard(const Board& , const std::vector<unique_ptr<FightInfo>>& )
{
    // leave empty on purpose
}

void FilePlayerAlgorithm::notifyOnOpponentMove(const Move& )
{
    // leave empty on purpose
}

void FilePlayerAlgorithm::notifyFightResult(const FightInfo& )
{
    // leave empty on purpose
}

unique_ptr<Move> FilePlayerAlgorithm::getMove()
{
    if (moveCount >= static_cast<unsigned int>(moves.size()))
        return illegalMove();
    
    return std::move(moves[moveCount]);
}

unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange()
{
    if (moveCount >= static_cast<unsigned int>(jokerChanges.size()))
        return illegalJokerChange();
    
    return std::move(jokerChanges[moveCount++]);
}

FilePlayerAlgorithm::~FilePlayerAlgorithm()
{

}

void FilePlayerAlgorithm::fillInitialPositions(std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
    std::ifstream initFile(initFileName);
    if (!initFile.good())
        return;
    
    std::string line;
    std::getline(initFile, line);
    while (initFile.good())
    {
        if (!line.empty())
            vectorToFill.push_back(parseInit(line));
        std::getline(initFile, line);
    }
    if (initFile.eof())
    {
        if (!line.empty())
            vectorToFill.push_back(parseInit(line));
    }
    initFile.close();
}

void FilePlayerAlgorithm::fillMovesJokers()
{
    std::ifstream movesFile(movesFileName);
    if (!movesFile.good())
        return;
    
    std::string line;
    std::getline(movesFile, line);
    while (movesFile.good())
    {
        if (!line.empty())
        {
            moves.push_back(parseMove(line));
            jokerChanges.push_back(parseJokerChange(line));
        }
        std::getline(movesFile, line);
    }
    if (movesFile.eof())
    {
        if (!line.empty())
        {
            moves.push_back(parseMove(line));
            jokerChanges.push_back(parseJokerChange(line));
        }
    }
    movesFile.close();
}

std::vector<std::string> FilePlayerAlgorithm::splitToTokens(const std::string& line)
{
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    std::getline(ss, token, ' ');
    while (ss.good())
    {
        if (token.length() > 0)
            tokens.push_back(std::move(token));
        
        std::getline(ss, token, ' ');
    }
    if (ss.eof())
    {
        if (token.length() > 0)
            tokens.push_back(std::move(token));
    }
    
    return tokens; // not returning using std::move in order to utilize RVO
}

std::unique_ptr<PiecePosition> FilePlayerAlgorithm::parseInit(const std::string& line)
{
    std::vector<std::string> tokens = std::move(splitToTokens(line));
    switch (tokens.size())
    {
        case 3:
            if (tokens[0].size() > 1)
                return illegalPiecePosition();
            try
            {
                int x = std::stoi(tokens[1]);
                int y = std::stoi(tokens[2]);
                return std::make_unique<PiecePositionImpl>(PointImpl(x, y), tokens[0].at(0), '#');
                
            } catch (...)
            {
                return illegalPiecePosition();
            }
        
        case 4:
            if (tokens[0] != "J")
                return illegalPiecePosition();
            try
            {
                int x = std::stoi(tokens[1]);
                int y = std::stoi(tokens[2]);
                if (tokens[3].size() > 1)
                    return illegalPiecePosition();
                return std::make_unique<PiecePositionImpl>(PointImpl(x, y), tokens[0].at(0), tokens[3].at(0));
                
            } catch (...)
            {
                return illegalPiecePosition();
            }
        default:
            return illegalPiecePosition();
    }
}

std::unique_ptr<PiecePosition> FilePlayerAlgorithm::illegalPiecePosition()
{
    return std::make_unique<PiecePositionImpl>(PointImpl(-1, -1), '#', '$');
}

std::unique_ptr<Move> FilePlayerAlgorithm::parseMove(const std::string& line)
{
    auto tokens = splitToTokens(line);
    switch (tokens.size())
    {
        case 4:
        case 8:
            try
            {
                int fromX = std::stoi(tokens[0]);
                int fromY = std::stoi(tokens[1]);
                int toX = std::stoi(tokens[2]);
                int toY = std::stoi(tokens[3]);
                return std::make_unique<MoveImpl>(PointImpl(fromX, fromY), PointImpl(toX, toY));
                
            } catch (...)
            {
                return illegalMove();
            }
        default:
            return illegalMove();
    }
}

std::unique_ptr<JokerChange> FilePlayerAlgorithm::parseJokerChange(const std::string& line)
{
    auto tokens = splitToTokens(line);
    switch (tokens.size())
    {
        case 4:
            return nullptr;
        case 8:
            try
            {
                if (tokens[4] != "J:")
                    return illegalJokerChange();
                int jX = std::stoi(tokens[5]);
                int jY = std::stoi(tokens[6]);
                if (tokens[7].size() > 1)
                    return illegalJokerChange();
                return std::make_unique<JokerChangeImpl>(PointImpl(jX, jY), tokens[7].at(0));
            } catch (...)
            {
                return illegalJokerChange();
            }
        default:
            return illegalJokerChange();
    }
}

std::unique_ptr<Move> FilePlayerAlgorithm::illegalMove()
{
    return std::make_unique<MoveImpl>(PointImpl(-1, -1), PointImpl(-1, -1));
}

std::unique_ptr<JokerChange> FilePlayerAlgorithm::illegalJokerChange()
{
    return std::make_unique<JokerChangeImpl>(PointImpl(-1, -1), '@');
}
