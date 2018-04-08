#include "GameBoard.h"

GameBoard::GameBoard() : board(M * N)
{

}


bool GameBoard::isLegalLocation(int xCoor, int yCoor) const
{
    if (xCoor < 1 || xCoor > M || yCoor < 1 || yCoor > N)
        return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const GameBoard& board)
{
    for (int yCoor = 1; yCoor <= board.N; yCoor++)
    {
        for (int xCoor = 1; xCoor <= board.M; xCoor++)
        {
            if (board.at(xCoor, yCoor) == nullptr)
                os << ' ';
            else
                os << board.at(xCoor, yCoor)->toChar();
        }
        os << std::endl;
    }
    return os;
}

const GamePiece* GameBoard::at(int xCoor, int yCoor) const
{
    
    return board[boardIdxToVecIdx(xCoor,yCoor)].get();
}

void GameBoard::changePiece(std::unique_ptr<GamePiece> newPiece, int xCoor, int yCoor)
{
    board[boardIdxToVecIdx(xCoor,yCoor)].swap(newPiece);
}


int GameBoard::boardIdxToVecIdx(int xCoor, int yCoor) const
{
    xCoor--;
    yCoor--;
    return yCoor * M + xCoor;
}
