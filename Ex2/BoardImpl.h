//
// Created by yanna on 05/07/18.
//

#ifndef EX2_BOARDIMPL_H
#define EX2_BOARDIMPL_H

#include <vector>
#include "Board.h"
#include "Point.h"

class BoardImpl : public Board
{
public:
    BoardImpl(int totalX,int totalY);
    int getPlayer(const Point& pos) const override;
    
    void setPlayer(const Point& pos, int playerID); // places a player on the board, assume all checks for legal placing happens outside

private:
    
    int getInd(const Point& pos) const; //returns the index in the vector corresponding the Point
    
    const totalX;
    const totalY;
    std::vector<int> board;
    
};


#endif //EX2_BOARDIMPL_H
