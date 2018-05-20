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
        setNoFlag(fightInfo.getPosition());
        auto& piece = getPiece(nonFlags, fightInfo.getPosition());
        if (piece != nullptr && piece->getPiece() != '?' && piece->getPiece() != fightInfo.getPiece(opponentId))
        {// known piece with different type -> its a joker
            updatePieceType(nonFlags, fightInfo.getPosition(), 'J', fightInfo.getPiece(opponentId));
        } else if (piece != nullptr)
        {
            updatePieceType(nonFlags, fightInfo.getPosition(), fightInfo.getPiece(opponentId));
        }
    } else if (fightInfo.getWinner() == BOTH)
    {
        removePiece(myPieces, fightInfo.getPosition());
        removePiece(assumedFlags, fightInfo.getPosition());
        removePiece(nonFlags, fightInfo.getPosition());
    }
}

unique_ptr<Move> AutoPlayerAlgorithm::getMove()
{
    const auto& from = chooseFrom();
    const auto& to = chooseTo(*from);
    
    board.setPlayer(*from, NONE);
    board.setPlayer(*to, myId);
    
    std::unique_ptr<Move> move = std::make_unique<MoveImpl>(*from, *to);
    
    updatePosition(myPieces, *move);
    return move;
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange()
{
    std::vector<const PiecePosition*> jokers;
    bool movableRemaining = false;
    
    for (const auto& piece:myPieces)
    {
        if (piece == nullptr)
            continue;
        
        if (isMovable(*piece))
        {
            movableRemaining = true;
        }
        
        if (piece->getPiece() != 'J')
            continue;
        
        // in here we hold a joker
        jokers.push_back(piece.get());
        
        auto neighbours = getAvailableMoves(piece->getPosition());
        for (const auto& neighbour:neighbours)
        {// look for an opponent neighbour with known type, switch to a stronger type
            if (neighbour.getOwner() == opponentId)
            {
                if (isMovable(neighbour.getPieceType(), neighbour.getJokerRep()))
                {
                    char neighbourType = neighbour.getPieceType();
                    if (neighbourType == 'J')
                        neighbourType = neighbour.getJokerRep();
                    char newType = getStrongerType(neighbourType);
                    return std::make_unique<JokerChangeImpl>(piece->getPosition(), newType);
                }
            }
        }
    }
    
    // no opponent neighbours with known type
    std::vector<char> movable{'R', 'P', 'S'};
    if (!jokers.empty() && !movableRemaining)
    {
        return std::make_unique<JokerChangeImpl>(jokers[0]->getPosition(), movable[generator.getRange(0, 2)]);
    }
    return nullptr;
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

std::unique_ptr<Point> AutoPlayerAlgorithm::chooseFrom() const
{
    std::vector<PointImpl> availableFromLocations;
    for (const auto& piece:myPieces)
    {
        if (piece == nullptr)
            continue;
        
        if (!isMovable(*piece))
            continue;
        
        auto neighbours = getAvailableMoves(piece->getPosition());
        if (!neighbours.empty())
            availableFromLocations.emplace_back(piece->getPosition());
    }
    
    if (availableFromLocations.empty())
        return std::make_unique<PointImpl>(-1, -1);
    
    
    return std::make_unique<PointImpl>(availableFromLocations[generator.getRange(0, static_cast<int>(availableFromLocations.size() - 1))]);
}

std::unique_ptr<Point> AutoPlayerAlgorithm::chooseTo(const Point& from) const
{
    if (!inBoard(from))
        return std::make_unique<PointImpl>(-1, -1);
    
    const auto neighbours = getAvailableMoves(from);
    if (neighbours.empty())
        return std::make_unique<PointImpl>(-1, -1);
    
    const auto& myPiece = getPiece(myPieces, from);
    if (myPiece == nullptr)
        return std::make_unique<PointImpl>(-1, -1);
    char myPieceType = getEffectiveType(myPiece->getPiece(), myPiece->getJokerRep());
    
    auto onlyFlagRemaining = testOnlyFlagsRemaining(neighbours);
    if (onlyFlagRemaining != nullptr)
        return onlyFlagRemaining;
    
    auto weakerOpponent = testWeakerNeighbour(neighbours, myPieceType);
    if (weakerOpponent != nullptr)
        return weakerOpponent;
    
    auto nearAssumedFlag = testAssumedFlagNeighbour(neighbours);
    if (nearAssumedFlag != nullptr)
        return nearAssumedFlag;
    
    auto nonFlagUnknownNeighbour = testUnknownNonFlagNeighbour(neighbours);
    if (nonFlagUnknownNeighbour != nullptr)
        return nonFlagUnknownNeighbour;
    
    auto freeSpot = testFreeSpot(neighbours);
    if (freeSpot != nullptr)
        return freeSpot;
    
    return std::make_unique<PointImpl>(-1, -1);
}

std::vector<BoardSpot> AutoPlayerAlgorithm::getAvailableMoves(const Point& from) const
{
    PointImpl above(from.getX(), from.getY() - 1);
    PointImpl below(from.getX(), from.getY() + 1);
    PointImpl left(from.getX() - 1, from.getY());
    PointImpl right(from.getX() + 1, from.getY());
    
    std::vector<PointImpl> directions{above, below, left, right};
    
    std::vector<BoardSpot> availableMoves;
    
    for (const auto& direction:directions)
    {
        if (!inBoard(direction))
            continue;
        
        const auto& myPiece = getPiece(myPieces, direction);
        if (myPiece != nullptr)
            continue;
        
        const auto& assumedFlagPiece = getPiece(assumedFlags, direction);
        if (assumedFlagPiece != nullptr)
        {
            availableMoves.emplace_back(direction, opponentId, assumedFlagPiece->getPiece(), assumedFlagPiece->getJokerRep(), true);
            continue;
        }
        const auto& nonFlagPiece = getPiece(nonFlags, direction);
        if (nonFlagPiece != nullptr)
        {
            availableMoves.emplace_back(direction, opponentId, nonFlagPiece->getPiece(), nonFlagPiece->getJokerRep(), false);
            continue;
        }
        
        availableMoves.emplace_back(direction, NONE, '#');
    }
    return availableMoves;
}

bool AutoPlayerAlgorithm::inBoard(const Point& p) const
{
    return (p.getX() >= 1 && p.getX() <= totalXVals && p.getY() >= 1 && p.getY() <= totalYVals);
}

bool AutoPlayerAlgorithm::isMovable(const PiecePosition& piece) const
{
    return isMovable(piece.getPiece(), piece.getJokerRep());
}

char AutoPlayerAlgorithm::getStrongerType(char type) const
{
    switch (type)
    {
        case 'R':
            return 'P';
        case 'P':
            return 'S';
        case 'S':
            return 'R';
        default:
            return '#';
    }
}

bool AutoPlayerAlgorithm::isMovable(char type, char jokerRep) const
{
    type = getEffectiveType(type, jokerRep);
    return (type == 'R' || type == 'P' || type == 'S');
}

const std::unique_ptr<PiecePosition>&
AutoPlayerAlgorithm::getPiece(const std::vector<std::unique_ptr<PiecePosition>>& pieces, const Point& location) const
{
    
    for (const auto& piece:pieces)
    {
        if (piece == nullptr)
            continue;
        if (piece->getPosition().getX() == location.getX() && piece->getPosition().getY() == location.getY())
            return piece;
        
    }
    return nullPiece;
}

int AutoPlayerAlgorithm::getRemaining(const std::vector<std::unique_ptr<PiecePosition>>& pieces) const
{
    int cnt = 0;
    for (const auto& piece:pieces)
    {
        if (piece != nullptr)
            cnt++;
    }
    return cnt;
}

char AutoPlayerAlgorithm::getEffectiveType(char type, char jokerRep) const
{
    if (type == 'J')
        return jokerRep;
    return type;
}

std::unique_ptr<Point> AutoPlayerAlgorithm::testAssumedFlagNeighbour(const std::vector<BoardSpot>& neighbours) const
{
    for (const auto& neighbour:neighbours)
    {
        if (neighbour.getOwner() == opponentId && neighbour.getAssumedFlag())
            return std::make_unique<PointImpl>(neighbour.getLocation());
    }
    return nullptr;
}

std::unique_ptr<Point> AutoPlayerAlgorithm::testOnlyFlagsRemaining(const std::vector<BoardSpot>& neighbours) const
{
    // only flags are left, attack a neighbour flag
    if (getRemaining(assumedFlags) <= totalFlags && getRemaining(nonFlags) == 0)
    {
        for (const auto& neighbour:neighbours)
        {
            if (neighbour.getOwner() == opponentId)
            {
                return std::make_unique<PointImpl>(neighbour.getLocation());
            }
        }
    }
    
    return nullptr;
}

std::unique_ptr<Point> AutoPlayerAlgorithm::testWeakerNeighbour(const std::vector<BoardSpot>& neighbours, char myPieceType) const
{
    for (const auto& neighbour:neighbours)
    {
        if (neighbour.getOwner() != opponentId)
            continue;
        
        if (getStrongerType(getEffectiveType(neighbour.getPieceType(), neighbour.getJokerRep())) == myPieceType)
            return std::make_unique<PointImpl>(neighbour.getLocation());
        
    }
    return nullptr;
}

std::unique_ptr<Point> AutoPlayerAlgorithm::testUnknownNonFlagNeighbour(const std::vector<BoardSpot>& neighbours) const
{
    for (const auto& neighbour:neighbours)
    {
        if (neighbour.getOwner() == opponentId && !neighbour.getAssumedFlag() && (neighbour.getPieceType() == '?' || neighbour.getPieceType() == '#'))
            return std::make_unique<PointImpl>(neighbour.getLocation());
    }
    return nullptr;
}

std::unique_ptr<Point> AutoPlayerAlgorithm::testFreeSpot(const std::vector<BoardSpot>& neighbours) const
{
    for (const auto& neighbour:neighbours)
    {
        if (neighbour.getOwner() == NONE)
            return std::make_unique<PointImpl>(neighbour.getLocation());
    }
    return nullptr;
}


