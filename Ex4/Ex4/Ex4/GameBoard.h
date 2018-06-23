#pragma once
#include <memory>
#include <array>

template <typename GAME_PIECE>
using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS = 2>
class GameBoard
{
	
public:
	PieceInfo<GAME_PIECE> getPiece(int row, int col) const; //returns the piece info of the piece in this location or nullptr if empty
	PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player); //sets the given piece in the chosen location
	class iterator;
	iterator begin() const;
	iterator end() const;

	class iterator
	{
	public:
		iterator(const GameBoard* myBoard);
		std::tuple<int, int, GAME_PIECE, int> operator*();
		iterator operator++();
		bool operator!=(const iterator& other);
	private:
		const GameBoard* myBoard;
		int currRow;
		typename std::array<PieceInfo<GAME_PIECE>, COLS>::const_iterator myArrIterator;

	};
	public :
	std::array<std::array<PieceInfo<GAME_PIECE>, COLS>, ROWS> board;
};


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

	board[row][col].swap(std::make_unique<const std::pair<int, GAME_PIECE>>(player, std::forward<GAME_PIECE>(piece)));

	return oldPiece;
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::begin() const
{
	iterator it = iterator(this);
	return it;

}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::end() const
{
	iterator it = iterator(this);

	return it;

}


template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::iterator(const GameBoard* _myBoard) :myBoard(_myBoard), currRow(0),myArrIterator(myBoard->board[0].cbegin())
{}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
std::tuple<int, int, GAME_PIECE, int> GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::operator*()
{
	return std::tuple<int, int, GAME_PIECE, int>(0, 0, 0, 0);
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
typename GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::operator++()
{
	return *this;
}

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
bool GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::operator!=(const iterator& other)
{
	return false;
}