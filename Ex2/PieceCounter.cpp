#include "PieceCounter.h"



PieceCounter::PieceCounter(int maxRocks, int maxPapers, int maxScissors, int maxBombs, int maxJokers, int maxFlags) :maxRocks(maxBombs), maxPapers(maxPapers), maxScissors(maxScissors), maxBombs(maxBombs), maxJokers(maxJokers), maxFlags(maxFlags)
{
	rocks = 0;
	papers = 0;
	scissors = 0;
	bombs = 0;
	jokers = 0;
	flags = 0;
}

PieceCounter::~PieceCounter()
{
}

bool PieceCounter::addPiece(char pieceChar)
{
	if (getRemaining(pieceChar) < 1)
		return false;
	switch (pieceChar)
	{
	case 'R':
	case 'r':
		rocks++;
		break;
	case 'P':
	case 'p':
		papers++;
		break;
	case 'S':
	case 's':
		scissors++;
		break;
	case 'B':
	case 'b':
		bombs++;
		break;
	case 'J':
	case 'j':
		jokers++;
		break;
	case 'F':
	case 'f':
		flags++;
		break;
	default:
		return false;
	}
	return true;
}

int PieceCounter::getRemaining(char pieceChar) const
{
	switch (pieceChar)
	{
	case 'R':
	case 'r':
		return maxRocks - rocks;
	case 'P':
	case 'p':
		return maxPapers - papers;
	case 'S':
	case 's':
		return maxScissors - scissors;
	case 'B':
	case 'b':
		return maxBombs - bombs;
	case 'J':
	case 'j':
		return maxJokers - jokers;
	case 'F':
	case 'f':
		return maxFlags - flags;
	default:
		return -1;
	}
}


