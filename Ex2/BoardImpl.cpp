//
// Created by yanna on 05/07/18.
//

#include "BoardImpl.h"

int BoardImpl::getPlayer(const Point& pos) const
{
    
    return board[getInd(pos)];
}

BoardImpl::BoardImpl(int totalX, int totalY) : totalX(totalX), totalY(totalY), board(totalX * totalY, 0)
{

}

int BoardImpl::getInd(const Point& pos) const
{
    int x = pos.getX();
    int y = pos.getY();
    int ind = (x-1) + (y-1)*totalX;
    
    return ind;
}

void BoardImpl::setPlayer(const Point& pos, int playerID)
{
    board[getInd(pos)] = playerID;
}
