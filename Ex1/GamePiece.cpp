

#include "GamePiece.h"

GamePiece::GamePiece(int ownerId, PieceType type) : ownerId(ownerId), type(type)
{

}

GamePiece::GamePiece(int ownerId, GamePiece::PieceType type, GamePiece::PieceType effectiveType) : GamePiece(ownerId, type)
{
    if (this->type == GamePiece::PieceType::Joker)
        this->effectiveType = effectiveType;
    else
        this->effectiveType = this->type;
}

bool operator>(const GamePiece& lPiece, const GamePiece& rPiece)
{
    if (lPiece == rPiece)
        return false;
    switch (lPiece.effectiveType)
    {
        case GamePiece::PieceType::Bomb: // bomb always wins
            return true;
        case GamePiece::PieceType::Flag: // flag always loses
            return false;
        case GamePiece::PieceType::Rock: // rock wins over scissors or flag
            if (rPiece.effectiveType == GamePiece::PieceType::Scissors || rPiece.effectiveType == GamePiece::PieceType::Flag)
                return true;
            return false;
        case GamePiece::PieceType::Paper: // paper wins over rock or flag
            if (rPiece.effectiveType == GamePiece::PieceType::Rock || rPiece.effectiveType == GamePiece::PieceType::Flag)
                return true;
            return false;
        case GamePiece::PieceType::Scissors: //scissors wins over paper or flag
            if (rPiece.effectiveType == GamePiece::PieceType::Paper || rPiece.effectiveType == GamePiece::PieceType::Flag)
                return true;
            return false;
        default:
            return false;
    }
}

bool operator<(const GamePiece& lPiece, const GamePiece& rPiece)
{
    return rPiece > lPiece;
}

bool operator==(const GamePiece& lPiece, const GamePiece& rPiece)
{
    return lPiece.effectiveType == rPiece.effectiveType;
}

bool GamePiece::isLegal() const
{
    if ((type == PieceType::Joker) && (effectiveType != PieceType::Joker) && (effectiveType != PieceType::Flag))
        return true;
    if ((type != PieceType::Joker) && (type == effectiveType))
        return true;
    return false;
}

bool GamePiece::changeType(GamePiece::PieceType newType)
{
    PieceType oldType = effectiveType;
    effectiveType = newType;
    bool legal = isLegal();
    if (!legal)
        effectiveType = oldType;
    return legal;
}

int GamePiece::getOwnerId() const
{
    return ownerId;
}
