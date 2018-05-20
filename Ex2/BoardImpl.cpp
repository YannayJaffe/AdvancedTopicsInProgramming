//
// Created by yanna on 05/07/18.
//

#include "BoardImpl.h"

int BoardImpl::getPlayer(const Point& pos) const
{
    if (pos.getX() > this->totalX || pos.getX() < 1 || pos.getY() > this->totalY || pos.getY() < 1)
        return -1;
    return board[getInd(pos)];
}

BoardImpl::BoardImpl(int totalX, int totalY) : totalX(totalX), totalY(totalY), board(totalX * totalY, 0)
{

}

int BoardImpl::getInd(const Point& pos) const
{
    int x = pos.getX();
    int y = pos.getY();
    int ind = (x - 1) + (y - 1) * totalX;
    
    return ind;
}

void BoardImpl::setPlayer(const Point& pos, int playerID)
{
    board[getInd(pos)] = playerID;
}

Board& BoardImpl::operator=(const Board& b)
{
    for (int x = 1; x < totalX; x++)
    {
        for (int y = 1; y < totalY; y++)
        {
            this->setPlayer(PointImpl(x,y),b.getPlayer(PointImpl(x,y)));
        }
    }
    return *this;
}
