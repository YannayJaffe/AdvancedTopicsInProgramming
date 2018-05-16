//
// Created by yanna on 05/07/18.
//

#ifndef EX2_FILEPLAYERALGORITHM_H
#define EX2_FILEPLAYERALGORITHM_H

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include "PlayerAlgorithm.h"
#include "PiecePosition.h"
#include "PiecePositionImpl.h"
#include "JokerChange.h"
#include "JokerChangeImpl.h"
#include "MoveImpl.h"

class FilePlayerAlgorithm : public PlayerAlgorithm
{
public:
    void getInitialPositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill) override;
    
    void notifyOnInitialBoard(const Board& b, const std::vector<std::unique_ptr<FightInfo>>& fights) override;
    
    void notifyOnOpponentMove(const Move& move) override;
    
    void notifyFightResult(const FightInfo& fightInfo) override;
    
    std::unique_ptr<Move> getMove() override;
    
    std::unique_ptr<JokerChange> getJokerChange() override;
    
    ~FilePlayerAlgorithm() override;
private:
    
    void fillInitialPositions(std::vector<std::unique_ptr<PiecePosition>>& vectorToFill);
    
    void fillMovesJokers();
    
    std::vector<std::string> splitToTokens(const std::string& line);
    
    std::unique_ptr<PiecePosition> parseInit(const std::string& line);
    
    std::unique_ptr<PiecePosition> illegalPiecePosition();
    
    std::unique_ptr<Move> illegalMove();
    
    std::unique_ptr<JokerChange> illegalJokerChange();
    
    std::unique_ptr<Move> parseMove(const std::string& line);
    
    std::unique_ptr<JokerChange> parseJokerChange(const std::string& line);
    
    int playerId;
    std::string initFileName;
    std::string movesFileName;
    std::vector<std::unique_ptr<Move>> moves;
    std::vector<std::unique_ptr<JokerChange>> jokerChanges;
    int moveCount;
};


#endif //EX2_FILEPLAYERALGORITHM_H
