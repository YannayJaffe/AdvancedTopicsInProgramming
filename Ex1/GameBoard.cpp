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
    
    return board[boardIdxToVecIdx(xCoor, yCoor)].get();
}

void GameBoard::changePiece(std::unique_ptr<GamePiece> newPiece, int xCoor, int yCoor)
{
    board[boardIdxToVecIdx(xCoor, yCoor)].swap(newPiece);
}


int GameBoard::boardIdxToVecIdx(int xCoor, int yCoor) const
{
    xCoor--;
    yCoor--;
    return yCoor * M + xCoor;
}

int GameBoard::getMovableCount(PlayerID player) const
{
    int cnt = 0;
    for (const auto& piece : board)
    {
        if (piece != nullptr && piece->getEffectiveType() != PieceType::Flag && piece->getEffectiveType() != PieceType::Bomb &&
            piece->getOwner() == player)
            cnt++;
    }
    return cnt;
}

int GameBoard::getFlagCount(PlayerID player) const
{
    int cnt = 0;
    for (const auto& piece : board)
    {
        if (piece != nullptr && piece->getEffectiveType() == PieceType::Flag && piece->getOwner() == player)
            cnt++;
    }
    return cnt;
}

bool GameBoard::isLegalLocation(const std::pair<int, int>& loc) const
{
    return isLegalLocation(loc.first, loc.second);
}

const GamePiece* GameBoard::at(const std::pair<int, int>& loc) const
{
    return at(loc.first,loc.second);
}

std::unique_ptr<GamePiece> GameBoard::removePiece(const std::pair<int, int>& loc)
{
    return removePiece(loc.first,loc.second);
}

std::unique_ptr<GamePiece> GameBoard::removePiece(int xCoor, int yCoor)
{
    std::unique_ptr<GamePiece> piece = nullptr;
    piece.swap(board[boardIdxToVecIdx(xCoor,yCoor)]);
    return piece;
}
