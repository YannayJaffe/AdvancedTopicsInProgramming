#ifndef EX1_GAMEBOARD_H
#define EX1_GAMEBOARD_H

#include "GamePiece.h"
#include <vector>
#include <memory>
#include <ostream>

class GameBoard
{
public:
    
    // allow to print the GameBoard
    friend std::ostream& operator<<(std::ostream& os, const GameBoard& board);

protected:
    GameBoard();
    
    bool isLegalLocation(int xCoor, int yCoor) const;
    
    bool isLegalLocation(const std::pair<int,int>& loc) const;
    
    //pre-condition: isLegalLocation(xCoor,yCoor)
    const GamePiece* at(int xCoor, int yCoor) const;
    const GamePiece* at(const std::pair<int,int>& loc) const;
    
    //pre-condition: isLegalLocation(xCoor,yCoor)
    //pre-condition: newPiece==nullptr or newPiece->isLegal()
    void changePiece(std::unique_ptr<GamePiece> newPiece, int xCoor, int yCoor);
    std::unique_ptr<GamePiece> removePiece(int xCoor,int yCoor);
    std::unique_ptr<GamePiece> removePiece(const std::pair<int,int>& loc);
    
    int getMovableCount(PlayerID player) const;
    
    int getFlagCount(PlayerID player) const;

private:
    //pre-condition: isLegalLocation(xCoor,yCoor)
    int boardIdxToVecIdx(int xCoor, int yCoor) const;
    
    static const int M = 10; // number of cols
    static const int N = 10; // number of rows
    
    
    // the board is a vector of pointers to game pieces. the vector is of length M*N
    std::vector<std::unique_ptr<GamePiece>> board;
    
};


#endif //EX1_GAMEBOARD_H
