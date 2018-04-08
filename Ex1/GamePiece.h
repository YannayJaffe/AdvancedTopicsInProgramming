#ifndef EX1_GAMEPIECE_H
#define EX1_GAMEPIECE_H

class GamePiece
{

public:
    enum class PieceType
    {
        Rock, Paper, Scissors, Bomb, Joker, Flag
    };
    
    GamePiece(int ownerId, PieceType type);
    
    GamePiece(int ownerId, PieceType type, PieceType effectiveType);
    
    bool isLegal() const;
    
    bool changeType(PieceType newType);
    
    int getOwnerId() const;
    
    friend bool operator>(const GamePiece& lPiece, const GamePiece& rPiece);
    
    friend bool operator<(const GamePiece& lPiece, const GamePiece& rPiece);
    
    friend bool operator==(const GamePiece& lPiece, const GamePiece& rPiece);

private:
    const PieceType type;
    PieceType effectiveType;
    const int ownerId;
    
};


#endif //EX1_GAMEPIECE_H
