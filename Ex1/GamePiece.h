#ifndef EX1_GAMEPIECE_H
#define EX1_GAMEPIECE_H

#include "GeneralDefinitions.h"

class GamePiece
{
public:
    GamePiece(PlayerID owner, PieceType type);
    
    GamePiece(PlayerID owner, PieceType type, PieceType effectiveType);
    
    bool isLegal() const;
    
    bool changeType(PieceType newType);
    
    friend bool operator>(const GamePiece& lPiece, const GamePiece& rPiece);
    
    friend bool operator<(const GamePiece& lPiece, const GamePiece& rPiece);
    
    friend bool operator==(const GamePiece& lPiece, const GamePiece& rPiece);
    
    char toChar() const;
    
    PieceType getEffectiveType() const;
    
    const PlayerID getOwner() const;
    
    const PieceType getType() const;
    
    bool isMovable() const;

private:
    const PieceType type;
    PieceType effectiveType;
    const PlayerID owner;
    
};


#endif //EX1_GAMEPIECE_H
