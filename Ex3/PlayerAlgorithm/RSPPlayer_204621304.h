//
// Created by yanna on 05/07/18.
//

#ifndef EX2_RSPPLAYER_204621304_H
#define EX2_RSPPLAYER_204621304_H

#include "PlayerAlgorithm.h"
#include "BoardImpl.h"
#include "PieceCounter.h"
#include "PiecePositionImpl.h"
#include "PointImpl.h"
#include "RandomGenerator.h"
#include "MoveImpl.h"
#include "BoardSpot.h"
#include "JokerChangeImpl.h"
#include "AlgorithmRegistration.h"

class RSPPlayer_204621304 : public PlayerAlgorithm
{
public:
    RSPPlayer_204621304();
    
    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
    
    void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
    
    void notifyOnOpponentMove(const Move& move) override;
    
    void notifyFightResult(const FightInfo& fightInfo) override;
    
    unique_ptr<Move> getMove() override;
    
    unique_ptr<JokerChange> getJokerChange() override;
    
    ~RSPPlayer_204621304() override = default;

protected:
    
    virtual std::unique_ptr<PiecePosition> generatePiece(const Board& board, const PieceCounter& counter);
    
    virtual std::unique_ptr<Point> chooseFrom() const;
    
    virtual std::unique_ptr<Point> chooseTo(const Point& from) const;

private:
    
    PointImpl findEmptySpot(const Board& board); // finds an empty spot on the given board
    std::unique_ptr<PiecePosition>& getPiece(std::vector<std::unique_ptr<PiecePosition>>& pieces, const Point& location); // return a piece
    
    const std::unique_ptr<PiecePosition>& getPiece(const std::vector<std::unique_ptr<PiecePosition>>& pieces, const Point& location) const; // return a piece
    
    bool setNoFlag(const Point& point);// this method declares that piece in spot point is non flag
    
    bool updatePosition(std::vector<std::unique_ptr<PiecePosition>>& pieces,
                        const Move& move); // updates the position of the piece in pieces according to move. false if there is no piece at move.from
    bool updatePieceType(std::vector<std::unique_ptr<PiecePosition>>& pieces, const Point& point, char type, char jokerType = '#');
    
    void removePiece(std::vector<std::unique_ptr<PiecePosition>>& pieces, const Point& point);
    
    std::vector<BoardSpot> getAvailableMoves(const Point& from) const;
    
    bool inBoard(const Point& p) const;
    
    bool isMovable(const PiecePosition& piece) const;
    
    bool isMovable(char type, char jokerRep = '#') const;
    
    char getStrongerType(char type) const;
    
    int getRemaining(const std::vector<std::unique_ptr<PiecePosition>>& pieces) const; // returns the amount of pieces in the vector
    
    char getEffectiveType(char type, char jokerRep) const;
    
    std::unique_ptr<Point> testOnlyFlagsRemaining(const std::vector<BoardSpot>& neighbours) const;
    
    std::unique_ptr<Point> testWeakerNeighbour(const std::vector<BoardSpot>& neighbours, char myPieceType) const;
    
    std::unique_ptr<Point> testAssumedFlagNeighbour(const std::vector<BoardSpot>& neighbours) const;
    
    std::unique_ptr<Point> testUnknownNonFlagNeighbour(const std::vector<BoardSpot>& neighbours) const;
    
    std::unique_ptr<Point> testFreeSpot(const std::vector<BoardSpot>& neighbours) const;
    
    BoardImpl board;
    std::vector<std::unique_ptr<PiecePosition>> myPieces;
    std::vector<std::unique_ptr<PiecePosition>> nonFlags;
    std::vector<std::unique_ptr<PiecePosition>> assumedFlags;
    int myId;
    int opponentId;
    const int PLAYER1 = 1;
    const int PLAYER2 = 2;
    const int BOTH = 0;
    const int NONE = 0;
    const int totalXVals = 10; //number of columns in the board (total x values)
    const int totalYVals = 10; // number of rows in the board (total y values)
    const int totalRocks = 2; // total Rocks
    const int totalPapers = 5; // total Papers
    const int totalScissors = 1; // total Scissors
    const int totalBombs = 2; // total Bombs
    const int totalJokers = 2; // total Jokers
    const int totalFlags = 1; // total Flags
    mutable RandomGenerator generator;
    std::unique_ptr<PiecePosition> nullPiece = nullptr; // a null piece to return if piece not found
    
    
};


#endif //EX2_AUTOPLAYERALGORITHM_H
