#ifndef EX1_GAMEPIECE_H
#define EX1_GAMEPIECE_H

#include "GeneralDefinitions.h"
#include <cctype>
class GamePiece
{

public:
    
    
    GamePiece(PlayerID ownerId, PieceType type);
    
    GamePiece(PlayerID ownerId, PieceType type, PieceType effectiveType);
    
    bool isLegal() const;
    
    bool changeType(PieceType newType);
    
    PlayerID getOwnerId() const;
    
    friend bool operator>(const GamePiece& lPiece, const GamePiece& rPiece);
    
    friend bool operator<(const GamePiece& lPiece, const GamePiece& rPiece);
    
    friend bool operator==(const GamePiece& lPiece, const GamePiece& rPiece);
    
    char toChar() const;

private:
    const PieceType type;
    PieceType effectiveType;
    const PlayerID ownerId;
    
};


#endif //EX1_GAMEPIECE_H
