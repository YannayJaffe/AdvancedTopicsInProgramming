#pragma once

#include <memory>
#include <array>

template <typename GAME_PIECE> using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS = 2>
class GameBoard
{
    class iterator;
    
    class PlayerView;
    
    class PieceView;
    
    class PlayerPieceView;

public:
    PieceInfo<GAME_PIECE> getPiece(int row, int col) const; //returns the piece info of the piece in this location or nullptr if empty
    PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player); //sets the given piece in the chosen location
    
    iterator begin() const;
    
    iterator end() const;
    
    PlayerView allPiecesOfPlayer(int playerNum);
    
    PieceView allOccureneceOfPiece(GAME_PIECE piece);
    
    PlayerPieceView allOccureneceOfPieceForPlayer(GAME_PIECE piece, int playerNum);

private:
    class iterator
    {
    public:
        iterator(const GameBoard* myBoard, int currRow, int currCol);
        
        virtual std::tuple<int, int, GAME_PIECE, int> operator*();
        
        virtual iterator operator++();
        
        virtual bool operator!=(const iterator& other);
    
    protected:
        const GameBoard* myBoard;
        int currRow;
        int currCol;
        
    };
    
    class PlayerView
    {
        class iterator;
    
    public:
        PlayerView(const GameBoard* myBoard, int playerNum);
        
        typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerView::iterator begin() const;
        
        typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerView::iterator end() const;
    
    private:
        class iterator : public GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator
        {
        public:
            iterator(const GameBoard* myBoard, int currRow, int currCol, int playerNum);
            
            GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator operator++() override;
        
        private:
            int playerNum;
        };
        
        const GameBoard* myBoard;
        int playerNum;
        
    };
    
    
    class PieceView
    {
        class iterator;
    
    public:
        PieceView(const GameBoard* myBoard, GAME_PIECE piece);
        
        typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PieceView::iterator begin() const;
        
        typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PieceView::iterator end() const;
    
    private:
        class iterator : public GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator
        {
        public:
            iterator(const GameBoard* myBoard, int currRow, int currCol, GAME_PIECE piece);
            
            GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator operator++() override;
        
        private:
            GAME_PIECE piece;
        };
        
        const GameBoard* myBoard;
        GAME_PIECE piece;
        
    };
    
    class PlayerPieceView
    {
        class iterator;
    
    public:
        PlayerPieceView(const GameBoard* myBoard, GAME_PIECE piece, int playerNum);
        
        typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerPieceView::iterator begin() const;
        
        typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerPieceView::iterator end() const;
    
    private:
        class iterator : public GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator
        {
        public:
            iterator(const GameBoard* myBoard, int currRow, int currCol, GAME_PIECE piece, int playerNum);
            
            GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator operator++() override;
        
        private:
            GAME_PIECE piece;
            int playerNum;
        };
        
        const GameBoard* myBoard;
        GAME_PIECE piece;
        int playerNum;
        
    };
    
    std::array<std::array<PieceInfo<GAME_PIECE>, COLS>, ROWS> board;
};

/*
==================================== GameBoard implementation ====================================
*/

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
PieceInfo<GAME_PIECE> GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::getPiece(int row, int col) const
{
    if (board[row][col] == nullptr)
        return nullptr;
    
    return std::make_unique<const std::pair<int, GAME_PIECE>>(*board[row][col]);
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
PieceInfo<GAME_PIECE> GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::setPiece(int row, int col, GAME_PIECE piece, int player)
{
    PieceInfo<GAME_PIECE> oldPiece = getPiece(row, col);
    
    board[row][col] = std::make_unique<const std::pair<int, GAME_PIECE>>(player, std::forward<GAME_PIECE>(piece));
    
    return oldPiece;
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::begin() const
{
    // begin will return an iterator pointing to the first non empty spot
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (board[row][col] != nullptr)
                return iterator(this, row, col);
        }
    }
    
    return end();
    
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::end() const
{
    iterator it = iterator(this, ROWS, 0);
    return it;
    
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerView GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::allPiecesOfPlayer(int playerNum)
{
    return PlayerView(this, playerNum);
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PieceView GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::allOccureneceOfPiece(GAME_PIECE piece)
{
    return GameBoard::PieceView(this, piece);
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerPieceView GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::allOccureneceOfPieceForPlayer(GAME_PIECE piece, int playerNum)
{
    return GameBoard::PlayerPieceView(this, piece, playerNum);
}

/*
================================ GameBoard::iterator implementation ===============================
*/

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::iterator(const GameBoard* _myBoard, int _currRow, int _currCol) :myBoard(_myBoard),
                                                                                                                       currRow(_currRow),
                                                                                                                       currCol(_currCol)
{}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
std::tuple<int, int, GAME_PIECE, int> GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::operator*()
{
    return std::tuple<int, int, GAME_PIECE, int>(currRow, currCol, myBoard->board[currRow][currCol]->second, myBoard->board[currRow][currCol]->first);
}


template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::operator++()
{
    while (true)
    {
        ++currCol;
        if (currCol >= COLS)
        {// go to the next row
            currCol = -1;
            if (++currRow >= ROWS)
            {//no more rows
                currRow = ROWS; // in case some evil user wants 0 rows
                currCol = 0;// so it will be the same as GameBoard::end
                return *this;
            }
            continue;
        }
        if (myBoard->board[currRow][currCol] != nullptr)
            break;
    }
    return *this;
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
bool GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::operator!=(const iterator& other)
{
    
    return (currCol != other.currCol || currRow != other.currRow);
    
}

/*
=============================== GameBoard::PlayerView implementation ==============================
*/

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerView::PlayerView(const GameBoard* _myBoard, int _playerNum):myBoard(_myBoard), playerNum(_playerNum)
{}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerView::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerView::begin() const
{
    
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (myBoard->board[row][col] != nullptr && myBoard->board[row][col]->first == playerNum)
                return iterator(myBoard, row, col, playerNum);
        }
    }
    return iterator(myBoard, ROWS, 0, playerNum);
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerView::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerView::end() const
{
    return iterator(myBoard, ROWS, 0, playerNum);
}

/*
========================== GameBoard::PlayerView::iterator implementation =========================
*/

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerView::iterator::iterator(const GameBoard* myBoard, int currRow, int currCol, int playerNum)
        :GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator(myBoard, currRow, currCol), playerNum(playerNum)
{

}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerView::iterator::operator++()
{
    while (*this != this->myBoard->end())
    {
        GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::operator++();
        
        if (*this != this->myBoard->end() && std::get<3>(**this) == playerNum)
        {
            break;
        }
    }
    return *this;
}

/*
=============================== GameBoard::PieceView implementation ==============================
*/

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PieceView::PieceView(const GameBoard* _myBoard, GAME_PIECE piece):myBoard(_myBoard), piece(piece)
{}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PieceView::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PieceView::begin() const
{
    
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (myBoard->board[row][col] != nullptr && myBoard->board[row][col]->second == piece)
                return iterator(myBoard, row, col, piece);
        }
    }
    return iterator(myBoard, ROWS, 0, piece);
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PieceView::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PieceView::end() const
{
    return iterator(myBoard, ROWS, 0, piece);
}

/*
========================== GameBoard::PieceView::iterator implementation =========================
*/

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PieceView::iterator::iterator(const GameBoard* myBoard, int currRow, int currCol, GAME_PIECE piece)
        :GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator(myBoard, currRow, currCol), piece(piece)
{

}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PieceView::iterator::operator++()
{
    while (*this != this->myBoard->end())
    {
        GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::operator++();
        
        if (*this != this->myBoard->end() && std::get<2>(**this) == piece)
        {
            break;
        }
    }
    return *this;
}

/*
=============================== GameBoard::PlayerPieceView implementation ==============================
*/

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerPieceView::PlayerPieceView(const GameBoard* _myBoard, GAME_PIECE piece, int playerNum):myBoard(
        _myBoard), piece(piece), playerNum(playerNum)
{}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerPieceView::iterator
GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerPieceView::begin() const
{
    
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (myBoard->board[row][col] != nullptr && myBoard->board[row][col]->second == piece && myBoard->board[row][col]->first == playerNum)
                return iterator(myBoard, row, col, piece, playerNum);
        }
    }
    return iterator(myBoard, ROWS, 0, piece, playerNum);
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerPieceView::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerPieceView::end() const
{
    return iterator(myBoard, ROWS, 0, piece, playerNum);
}

/*
========================== GameBoard::PieceView::iterator implementation =========================
*/

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerPieceView::iterator::iterator(const GameBoard* myBoard, int currRow, int currCol, GAME_PIECE piece, int playerNum)
        :GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator(myBoard, currRow, currCol), piece(piece), playerNum(playerNum)
{

}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::PlayerPieceView::iterator::operator++()
{
    while (*this != this->myBoard->end())
    {
        GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::operator++();
        
        if (*this != this->myBoard->end() && std::get<2>(**this) == piece && std::get<3>(**this) == playerNum)
        {
            break;
        }
    }
    return *this;
}