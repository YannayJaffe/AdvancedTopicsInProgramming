//
// Created by yanna on 05/07/18.
//

#include "FilePlayerAlgorithm.h"

void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
    //treat this method as some kind of init to load positioning from relevant files
    
}

void FilePlayerAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights)
{
    // leave empty on purpose
}

void FilePlayerAlgorithm::notifyOnOpponentMove(const Move& move)
{
    // leave empty on purpose
}

void FilePlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo)
{
    // leave empty on purpose
}

unique_ptr<Move> FilePlayerAlgorithm::getMove()
{
    // load next move from file
    //if EOF/bad line format generate illegal move/nullptr
    return unique_ptr<Move>();
}

unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange()
{
    // if no joker change on current move than return nullptr. if illegal format nullptr/generate illegal move (check website)
    return unique_ptr<JokerChange>();
}

FilePlayerAlgorithm::~FilePlayerAlgorithm()
{

}
