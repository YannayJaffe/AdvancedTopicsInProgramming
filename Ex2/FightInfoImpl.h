#ifndef EX2_FIGHT_INFO_IMPL
#define EX2_FIGHT_INFO_IMPL

#include "C:\Git\AdvancedTopicsInProgramming\Ex2\FightInfo.h"
#include "C:\Git\AdvancedTopicsInProgramming\Ex2\Ex2\Ex2\PointImpl.h"
class FightInfoImpl :
	public FightInfo
{
public:
	FightInfoImpl(char player1Piece, char player2Piece, const Point& point, int winner) :player1Piece(player1Piece), player2Piece(player2Piece), point(point), winner(winner) {}
	~FightInfoImpl() = default;
	const Point& getPosition() const override { return point; }
	char getPiece(int player) const override // R, P, S, B or F (but NOT J)
	{
		if (player == 1)
			return player1Piece;
		else if (player == 2)
			return player2Piece;
		else
			return '#';
	}
	int getWinner() const override { return winner; } // 0 - both lost / tie, 1 - player 1 won, 2 - player 2 won
private:
	const char player1Piece;
	const char player2Piece;
	const PointImpl point;
	const int winner;

};
#endif

