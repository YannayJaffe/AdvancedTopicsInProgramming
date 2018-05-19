//
// Created by yanna on 05/07/18.
//

#include "AutoPlayerAlgorithm.h"

const int AutoPlayerAlgorithm::PLAYER1;
const int AutoPlayerAlgorithm::PLAYER2;
const int AutoPlayerAlgorithm::NONE;
const int AutoPlayerAlgorithm::BOTH;
const int AutoPlayerAlgorithm::totalXVals;
const int AutoPlayerAlgorithm::totalYVals;
const int AutoPlayerAlgorithm::totalRocks;
const int AutoPlayerAlgorithm::totalPapers;
const int AutoPlayerAlgorithm::totalScissors;
const int AutoPlayerAlgorithm::totalBombs;
const int AutoPlayerAlgorithm::totalJokers;
const int AutoPlayerAlgorithm::totalFlags;


void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill)
{
    myId = player;
    opponentId = (myId == PLAYER1) ? PLAYER2 : PLAYER1;
    BoardImpl tempBoard(totalYVals, totalYVals);
    PieceCounter tempCounter(totalRocks, totalPapers, totalScissors, totalBombs, totalJokers, totalFlags);
    while (true)
    {
        auto newPiece = generatePiece(tempBoard, tempCounter);
        if (newPiece == nullptr)
            break;
        
        tempBoard.setPlayer(newPiece->getPosition(), myId);
        if (!tempCounter.addPiece(newPiece->getPiece()))
            break;
        
        auto dupPiece = std::make_unique<PiecePositionImpl>(*newPiece);
        vectorToFill.push_back(std::move(newPiece));
        myPieces.push_back(std::move(dupPiece));
    }
}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights)
{
    board = b;
    for (int x = 1; x < totalYVals; x++)
    {
        for (int y = 1; y < totalYVals; y++)
        {
            if (board.getPlayer(PointImpl(x, y)) == opponentId)
            {
                std::unique_ptr<PiecePosition> opPiece = std::make_unique<PiecePositionImpl>(PointImpl(x, y), '?', '?');
                assumedFlags.push_back(std::move(opPiece));
            }
        }
    }
    
    for (const auto& fight:fights)
    {
        notifyFightResult(*fight);
    }
}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move& move)
{
    board.setPlayer(move.getFrom(), NONE);
    board.setPlayer((move.getTo()), opponentId); // anyway update with opponent id, maybe will be updated again after a fight
    
    setNoFlag(move.getFrom());
    if (updatePosition(nonFlags, move))
    {
        auto& piece = getPiece(nonFlags, move.getTo());
        if (piece != nullptr && piece->getPiece() == 'B')
        {
            updatePieceType(nonFlags, move.getTo(), 'J', '?');
        }
    }
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo)
{
    board.setPlayer(fightInfo.getPosition(), fightInfo.getWinner());
    
    if (fightInfo.getWinner() == myId)
    {
        removePiece(assumedFlags, fightInfo.getPosition());
        removePiece(nonFlags, fightInfo.getPosition());
        
    } else if (fightInfo.getWinner() == opponentId)
    {
        removePiece(myPieces, fightInfo.getPosition());
        //update
    } else if (fightInfo.getWinner() == BOTH)
    {
        removePiece(myPieces, fightInfo.getPosition());
        removePiece(assumedFlags, fightInfo.getPosition());
        removePiece(nonFlags, fightInfo.getPosition());
    }
}

unique_ptr<Move> AutoPlayerAlgorithm::getMove()
{
    return unique_ptr<Move>();
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange()
{
    return unique_ptr<JokerChange>();
}


AutoPlayerAlgorithm::AutoPlayerAlgorithm() : board(totalXVals, totalYVals)
{

}

std::unique_ptr<PiecePosition> AutoPlayerAlgorithm::generatePiece(const Board& board, const PieceCounter& counter)
{
    const std::vector<char> pieceTypes{'F', 'J', 'B', 'S', 'P', 'R'};
    for (auto pType:pieceTypes)
    {
        if (counter.getRemaining(pType) > 0)
        {
            char jokerRep = '#';
            if (pType == 'J')
            {
                jokerRep = 'S';
            }
            PointImpl loc = findEmptySpot(board);
            return std::make_unique<PiecePositionImpl>(loc, pType, jokerRep);
        }
    }
    return nullptr;
}

PointImpl AutoPlayerAlgorithm::findEmptySpot(const Board& board)
{
    std::vector<PointImpl> emptySpots;
    // find all empty spots on board
    for (int x = 1; x <= totalXVals; x++)
    {
        for (int y = 1; y <= totalYVals; y++)
        {
            if (board.getPlayer(PointImpl(x, y)) == NONE)
                emptySpots.emplace_back(x, y);
        }
    }
    if (emptySpots.empty())
        return PointImpl(-1, -1);
    
    return emptySpots[generator.getRange(0, static_cast<int>(emptySpots.size() - 1))]; // return a spot at random
    
    
    
}

std::unique_ptr<PiecePosition>& AutoPlayerAlgorithm::getPiece(std::vector<std::unique_ptr<PiecePosition>>& pieces, const Point& location)
{
    for (auto& piece:pieces)
    {
        if (piece == nullptr)
            continue;
        if (piece->getPosition().getX() == location.getX() && piece->getPosition().getY() == location.getY())
            return piece;
        
    }
    return nullPiece;
}

bool AutoPlayerAlgorithm::setNoFlag(const Point& point)
{
    auto& piece = getPiece(assumedFlags, point);
    if (piece == nullptr)
        return false;
    
    std::unique_ptr<PiecePosition> newPiece = nullptr;
    newPiece.swap(piece);
    nonFlags.push_back(std::move(newPiece));
    return true;
}

bool AutoPlayerAlgorithm::updatePosition(std::vector<std::unique_ptr<PiecePosition>>& pieces, const Move& move)
{
    auto& piece = getPiece(pieces, move.getFrom());
    if (piece == nullptr)
        return false;
    
    std::unique_ptr<PiecePosition> newPiece = std::make_unique<PiecePositionImpl>(move.getTo(), piece->getPiece(), piece->getJokerRep());
    piece.swap(newPiece);
    return true;
}

bool AutoPlayerAlgorithm::updatePieceType(std::vector<std::unique_ptr<PiecePosition>>& pieces, const Point& point, char type, char jokerType)
{
    auto& piece = getPiece(pieces, point);
    if (piece == nullptr)
        return false;
    
    std::unique_ptr<PiecePosition> newPiece = std::make_unique<PiecePositionImpl>(point, type, jokerType);
    piece.swap(newPiece);
    return true;
}

void AutoPlayerAlgorithm::removePiece(std::vector<std::unique_ptr<PiecePosition>>& pieces, const Point& point)
{
    auto& piece = getPiece(pieces, point);
    piece = nullptr;
}


