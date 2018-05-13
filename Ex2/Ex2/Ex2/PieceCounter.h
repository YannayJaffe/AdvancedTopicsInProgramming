#ifndef EX2_PIECE_COUNTER
#define EX2_PIECE_COUNTER
class PieceCounter
{
public:
	PieceCounter(int maxRocks, int maxPapers, int maxScissors, int maxBombs, int maxJokers, int maxFlags);
	~PieceCounter();
	bool addPiece(char pieceChar);//adds selected piece, returns true if addition was successful or false if not
	int getRemaining(char pieceChar); // returns the remaining ammount of selected piece type
private:
	const int maxRocks;
	const int maxPapers;
	const int maxScissors;
	const int maxBombs;
	const int maxJokers;
	const int maxFlags;

	int rocks;
	int papers;
	int scissors;
	int bombs;
	int jokers;
	int flags;
};
#endif
