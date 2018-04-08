


#include "GamePiece.h"

GamePiece::GamePiece(PlayerID ownerId, PieceType type) : ownerId(ownerId), type(type)
{
    effectiveType = type;
}

GamePiece::GamePiece(PlayerID ownerId, PieceType type, PieceType effectiveType) : GamePiece(ownerId, type)
{
    if (this->type == PieceType::Joker)
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
        case PieceType::Bomb: // bomb always wins
            return true;
        case PieceType::Flag: // flag always loses
            return false;
        case PieceType::Rock: // rock wins over scissors or flag
            if (rPiece.effectiveType == PieceType::Scissors || rPiece.effectiveType == PieceType::Flag)
                return true;
            return false;
        case PieceType::Paper: // paper wins over rock or flag
            if (rPiece.effectiveType == PieceType::Rock || rPiece.effectiveType == PieceType::Flag)
                return true;
            return false;
        case PieceType::Scissors: //scissors wins over paper or flag
            if (rPiece.effectiveType == PieceType::Paper || rPiece.effectiveType == PieceType::Flag)
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

bool GamePiece::changeType(PieceType newType)
{
    PieceType oldType = effectiveType;
    effectiveType = newType;
    bool legal = isLegal();
    if (!legal)
        effectiveType = oldType;
    return legal;
}

PlayerID GamePiece::getOwnerId() const
{
    return ownerId;
}

char GamePiece::toChar() const
{
    char c;
    switch (type)
    {
        case PieceType::Rock:
            c = 'r';
            break;
        case PieceType::Paper:
            c = 'p';
            break;
        case PieceType::Scissors:
            c = 's';
            break;
        case PieceType::Bomb:
            c = 'b';
            break;
        case PieceType::Joker:
            c = 'j';
            break;
        case PieceType::Flag:
            c = 'f';
            break;
    }
    if (ownerId == PlayerID::Player1)
        return static_cast<char>(toupper(c));
    return c;
}
