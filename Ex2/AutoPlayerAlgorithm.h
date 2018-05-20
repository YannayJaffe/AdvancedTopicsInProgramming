//
// Created by yanna on 05/07/18.
//

#ifndef EX2_AUTOPLAYERALGORITHM_H
#define EX2_AUTOPLAYERALGORITHM_H

#include "PlayerAlgorithm.h"
#include "BoardImpl.h"
#include "PieceCounter.h"
#include "PiecePositionImpl.h"
#include "PointImpl.h"
#include "RandomGenerator.h"
#include "MoveImpl.h"
#include "BoardSpot.h"
#include "JokerChangeImpl.h"

class AutoPlayerAlgorithm : public PlayerAlgorithm
{
public:
    AutoPlayerAlgorithm();
    AutoPlayerAlgorithm(unsigned int seed);
    
    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
    
    void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
    
    void notifyOnOpponentMove(const Move& move) override;
    
    void notifyFightResult(const FightInfo& fightInfo) override;
    
    unique_ptr<Move> getMove() override;
    
    unique_ptr<JokerChange> getJokerChange() override;
    
    ~AutoPlayerAlgorithm() override = default;

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
    static const int PLAYER1 = 1;
    static const int PLAYER2 = 2;
    static const int BOTH = 0;
    static const int NONE = 0;
    static const int totalXVals = 10; //number of columns in the board (total x values)
    static const int totalYVals = 10; // number of rows in the board (total y values)
    static const int totalRocks = 2; // total Rocks
    static const int totalPapers = 5; // total Papers
    static const int totalScissors = 1; // total Scissors
    static const int totalBombs = 2; // total Bombs
    static const int totalJokers = 2; // total Jokers
    static const int totalFlags = 1; // total Flags
    mutable RandomGenerator generator;
    std::unique_ptr<PiecePosition> nullPiece = nullptr; // a null piece to return if piece not found
    
    
};


#endif //EX2_AUTOPLAYERALGORITHM_H
