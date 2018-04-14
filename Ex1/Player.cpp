#include "Player.h"

Player::Player(PlayerID id, GameBoardForPlayers& board, const std::string& playerBoard, const std::string& playerMoves) : id(id), board(board),
                                                                                                                          playerBoard(playerBoard),
                                                                                                                          playerMoves(playerMoves),
                                                                                                                          moveFactory(playerMoves)
{
    state = PlayerState::UNINIT;
    rCountInFile = 0;
    pCountInFile = 0;
    sCountInFile = 0;
    bCountInFile = 0;
    jCountInFile = 0;
    fCountInFile = 0;
    points = 0;
    movablePiecesCount = 0;
    lineCnt = 0;
}

int Player::initBoard()
{
    int lineNum = 0;
    bool lineOk = true;
    bool isEmptyLine = true;
    InitFactory initFactory(playerBoard);
    if (!initFactory.init())
    {// couldnt open board placement file
        state = PlayerState::UNINIT;
        return 0;
    }
    state = PlayerState::INIT_OPENED;
    while (initFactory.anyLeft() && lineOk)
    {
        std::unique_ptr<GameInit> nextInit(static_cast<GameInit*>(initFactory.getNext(lineOk, isEmptyLine).release()));
        lineNum++;
        if (isEmptyLine)
            continue;
        if (lineOk)
        {
            auto linePiece = static_cast<PieceType>(nextInit->isJoker() ? PieceType::Joker : nextInit->getNewType());
            if (!hasRemainingPieces(linePiece))
            {
                lineOk = false;
                lastErrorString = "Not enough pieces";
                break;
            }
            if (!board.isLegalLocation(nextInit->getNewLocation().first, nextInit->getNewLocation().second))
            {
                lineOk = false;
                lastErrorString = "Location out of board";
                break;
            }
            const GamePiece* piece = board.at(nextInit->getNewLocation().first, nextInit->getNewLocation().second);
            std::unique_ptr<GamePiece> newPiece;
            if (nextInit->isJoker())
            {
                newPiece = std::make_unique<GamePiece>(id, PieceType::Joker, nextInit->getNewType());
                jCountInFile++;
            } else
            {
                newPiece = std::make_unique<GamePiece>(id, nextInit->getNewType());
                switch (nextInit->getNewType())
                {
                    case PieceType::Bomb:
                        bCountInFile++;
                        break;
                    case PieceType::Rock:
                        rCountInFile++;
                        break;
                    case PieceType::Paper:
                        pCountInFile++;
                        break;
                    case PieceType::Scissors:
                        sCountInFile++;
                        break;
                    case PieceType::Joker:
                        lineOk = false;
                        lastErrorString = "Bad file format";
                        break;
                    case PieceType::Flag:
                        fCountInFile++;
                        break;
                }
                if (!lineOk)
                    break;
            }
            
            if (piece == nullptr)
            {
                board.changePiece(std::move(newPiece), nextInit->getNewLocation().first, nextInit->getNewLocation().second);
                continue;
            }
            if (piece->getOwner() == id)
            {
                lineOk = false;
                lastErrorString = "has already a piece at this location";
                break;
            } else
            {
                if (piece->getEffectiveType() == PieceType::Bomb || newPiece->getEffectiveType() == PieceType::Bomb || *piece == *newPiece)
                {
                    board.changePiece(nullptr, nextInit->getNewLocation().first, nextInit->getNewLocation().second);
                    continue;
                }
                if (*newPiece > *piece)
                {
                    board.changePiece(std::move(newPiece), nextInit->getNewLocation().first, nextInit->getNewLocation().second);
                    continue;
                }
            }
            
        } else
        {
            lastErrorString = "Bad file format";
            break;
        }
        
    }
    if (isEmptyLine)
        return 0;
    if (lineOk)
    {
        if (board.getFlagCount(id) != F)
        {
            lastErrorString = "didn't use all flags";
            state = PlayerState::INIT_OPENED;
            lineOk = false;
        }
    }
    state = lineOk ? PlayerState::INIT_DONE : PlayerState::INIT_OPENED;
    return lineOk ? 0 : lineNum;
}

bool Player::initMoves()
{
    if (!moveFactory.init())
    {
        state = PlayerState::UNINIT;
        return false;
    }
    state = PlayerState::MOVE_OPENED;
    return true;
}

std::string Player::toString()
{
    if (id == PlayerID::Player1)
        return "player 1";
    else if (id == PlayerID::Player2)
        return "player 2";
    else
        return "unknown player";
}

Player::PlayerState Player::getState() const
{
    return state;
}

bool Player::hasRemainingPieces(PieceType pieceType) const
{
    switch (pieceType)
    {
        case PieceType::Flag:
            return fCountInFile < F;
            break;
        case PieceType::Bomb:
            return bCountInFile < B;
            break;
        case PieceType::Scissors:
            return sCountInFile < S;
            break;
        case PieceType::Paper:
            return pCountInFile < P;
            break;
        case PieceType::Rock:
            return rCountInFile < R;
            break;
        case PieceType::Joker:
            return jCountInFile < J;
    }
}

const std::string& Player::getLastErrorString() const
{
    return lastErrorString;
}

const PlayerID Player::getId() const
{
    return id;
}

void Player::addPoint()
{
    points++;
}

int Player::getPoints() const
{
    return points;
}

bool Player::hasMovablePieces() const
{
    return (board.getMovableCount(id) > 0);
}

bool Player::hasMoreFlags() const
{
    return (board.getFlagCount(id) > 0);
}

bool Player::hasMoreMoves() const
{
    return moveFactory.anyLeft();
}

bool Player::playMove()
{
    bool isValidMove = true;
    bool isEmptyLine = false;
    std::unique_ptr<GameMove> gameMove(static_cast<GameMove*>(moveFactory.getNext(isValidMove, isEmptyLine).release()));
    lineCnt++;
    if (!isValidMove)
    {
        lastErrorString = "Bad format for move";
        return false;
    }
    if (isEmptyLine)
    {
        return true;
    }
    if (!board.isLegalLocation(gameMove->getPrevLocation()) || !board.isLegalLocation(gameMove->getNewLocation()) ||
        (gameMove->isJoker() && !board.isLegalLocation(gameMove->getJokerLocation())))
    {
        lastErrorString = "initial/final/joker position is out of bounds";
        return false;
    }
    
    
    return true;
}
