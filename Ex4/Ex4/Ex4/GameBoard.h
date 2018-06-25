#pragma once
#include <memory>
#include <array>

template <typename GAME_PIECE>
using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

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
		std::tuple<int, int, GAME_PIECE, int> operator*();
		iterator operator++();
		bool operator!=(const iterator& other);
	private:
		const GameBoard* myBoard;
		int currRow;
		int currCol;

	};

	class PlayerView
	{
		class iterator;

	public:		
		iterator begin();
		iterator end();
	private:
		class iterator: public GameBoard::iterator
		{

		};

	};

	class PieceView
	{
		class iterator;
	public:
		iterator begin();
		iterator end();
	private:
		class iterator
		{

		};
	};

	class PlayerPieceView
	{
		class iterator;
	public:
		iterator begin();
		iterator end();
	private:
		class iterator :public GameBoard::PlayerView::iterator
		{

		};
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

	board[row][col].swap(std::make_unique<const std::pair<int, GAME_PIECE>>(player, std::forward<GAME_PIECE>(piece)));

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

/*
================================ GameBoard::iterator implementation ===============================
*/

template <int ROWS, int COLS, class GAME_PIECE, int PLAYERS>
GameBoard<ROWS, COLS, GAME_PIECE, PLAYERS>::iterator::iterator(const GameBoard* _myBoard, int _currRow, int _currCol) :myBoard(_myBoard), currRow(_currRow), currCol(_currCol)
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