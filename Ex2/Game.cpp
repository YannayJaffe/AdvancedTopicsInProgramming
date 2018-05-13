//
// Created by yanna on 05/07/18.
//

#include "Game.h"

Game::Game(int argc, char** argv) : player1Algo(AlgoType::FILE), player2Algo(AlgoType::FILE), player1(nullptr), player2(nullptr), board(totalXVals, totalYVals),
totalMoves(0)
{
	if (argc < 2)
	{
		isLegalCommandLine = false;
	}
	else
	{
		isLegalCommandLine = true;
		std::string commandLine(argv[2]);
		if (commandLine.compare("auto-vs-file") == 0)
		{
			player1Algo = AlgoType::AUTO;
			player2Algo = AlgoType::FILE;

		}
		else if (commandLine.compare("file-vs-auto") == 0)
		{
			player1Algo = AlgoType::FILE;
			player2Algo = AlgoType::AUTO;

		}
		else if (commandLine.compare("auto-vs-auto") == 0)
		{
			player1Algo = AlgoType::AUTO;
			player2Algo = AlgoType::AUTO;
		}
		else if (commandLine.compare("file-vs-file") == 0)
		{
			player1Algo = AlgoType::FILE;
			player2Algo = AlgoType::FILE;

		}
		else
		{
			isLegalCommandLine = false;
		}
	}


}

bool Game::initPlayersPtrs()
{
	if (!isLegalCommandLine)
		return false;

	switch (player1Algo)
	{
	case AlgoType::FILE:
		player1 = std::make_unique<FilePlayerAlgorithm>();
		break;
	case AlgoType::AUTO:
		player1 = std::make_unique<AutoPlayerAlgorithm>();
		break;
	}

	switch (player2Algo)
	{
	case AlgoType::FILE:
		player2 = std::make_unique<FilePlayerAlgorithm>();
		break;
	case AlgoType::AUTO:
		player2 = std::make_unique<AutoPlayerAlgorithm>();
		break;
	}
	return (player1 != nullptr && player2 != nullptr);
}

void Game::runGame()
{
	if (!gameInit())
	{
		//if we got in here it means that the game is finished (bad files/bad arguments...)

		return;
	}
	// in here we have both of the players piece vectors initialized and valid


	// notify both players on initial board and fights

	// TODO: implement game moves etc.. look again at winner conditions
	// play the game in turns (player 1 moves first): 
	// 1. check how many moves played so far, if more than the max, declare tie.
	// 2. get a play from player, and check validity: first try to move the requested piece, if no more movable pieces, than declare winner
	// 3. when moving the piece, check if a fight happens.
	// 4. update both players pieces vectors, notify both players on the fight, and update the fights vector and board placement.
	// 5. notify other player on the move.
	// 6. after moved the piece, check for a joker change (again, check validity).
	// 7. if a joker change occured, update the player piece vector.
	// 8. check for remaining flags, declare winner if neccessary
	// 9. update moves counter

}

bool Game::checkInitialLegalPieces(const std::vector<std::unique_ptr<PiecePosition>>& playerPieces) const
{
	BoardImpl tempBoard(totalXVals, totalYVals);
	int id = 1; // in here we check for a single player legallity so the id doesnt matter
	PieceCounter tempPieceCounter(totalRocks, totalPapers, totalScissors, totalBombs, totalJokers, totalFlags);
	for (const auto& piece : playerPieces)
	{
		if (piece == nullptr)
			continue;

		if (!pointInBoard(piece->getPosition()))
			return false;//piece is out of board

		if (!tempPieceCounter.addPiece(piece->getPiece()))
			return false;//bad piece char or trying to add to many pieces

		if (tempBoard.getPlayer(piece->getPosition()) != 0)
			return false;//trying to add piece to an already occupied spot by the same player

		tempBoard.setPlayer(piece->getPosition(), id);
	}
	return (tempPieceCounter.getRemaining('F') == 0); // need to use all flags
}

bool Game::pointInBoard(const Point & p) const
{
	int x = p.getX();
	int y = p.getY();
	if ((x >= 1 && x <= totalXVals) && (y >= 1 && y <= totalYVals))
		return true;
	return false;
}

void Game::initBoard()
{
	// set player1 pieces on board - dont check for fights
	
	//set player 2 pieces on board (and conduct fights)
		
	// whenever a fight occurs create a FightInfo object and update the relevant vectors

}

void Game::initPlayerOnBoard(int playerId)
{ // when calling this method the board can be initialized properly
	std::vector<std::unique_ptr<PiecePosition>>* playerPieces;
	std::vector<std::unique_ptr<PiecePosition>>* otherPlayerPieces;
	if (playerId == 1)
	{
		playerPieces = &player1Pieces;
		otherPlayerPieces = &player2Pieces;
	}
	else if (playerId == 2)
	{
		playerPieces = &player2Pieces;
		otherPlayerPieces = &player1Pieces;
	}
	else
		return;

	int otherPlayerId = (playerId == 1 ? 2 : 1);

	for (auto& piece : *playerPieces)
	{
		if (piece == nullptr)
			continue;

		if (board.getPlayer(piece->getPosition()) == 0)
		{ // the board location is empty, can safely place the piece
			board.setPlayer(piece->getPosition(),playerId);
		}
		else if (board.getPlayer(piece->getPosition()) == otherPlayerId)
		{
			// the board location is occupied, conduct fight
			auto& otherPiece = getPlayerPiece(otherPlayerId, piece->getPosition());
			// continue working here

		}
	}
}

std::unique_ptr<PiecePosition>& Game::getPlayerPiece(int playerId, const Point & point) 
{
	std::vector<std::unique_ptr<PiecePosition>>* playerPieces;
	if (playerId == 1)
	{
		playerPieces = &player1Pieces;
	}
	else if (playerId == 2)
	{
		playerPieces = &player2Pieces;
	}
	else
		return nullPiecePosition;

	for (int i = 0; i < playerPieces->size(); i++)
	{
		if (playerPieces->at(i) == nullptr)
			continue;

		if (playerPieces->at(i)->getPosition().getX() == point.getX() && playerPieces->at(i)->getPosition().getY() == point.getY())
			return playerPieces->at(i);
	}
	return nullPiecePosition;
}

std::unique_ptr<FightInfo> Game::getFightInfo(const PiecePosition& player1Piece, const PiecePosition& player2Piece)
{
	char player1Type = player1Piece.getPiece();
	char player2Type = player2Piece.getPiece();
	if (player1Type == 'J' || player1Type == 'j')
		player1Type = player1Piece.getJokerRep();
	if (player2Type == 'J' || player2Type == 'j')
		player2Type = player2Piece.getJokerRep();
	
	std::unique_ptr<FightInfo> fightInfo = nullptr;
	
	return fightInfo;



	return std::unique_ptr<FightInfo>();
}

bool Game::operator>(const PiecePosition & p1, const PiecePosition & p2)
{
	char piece1 = p1.getPiece();
	if (piece1 == 'J' || piece1 == 'j')
		piece1 = p1.getJokerRep();
	char piece2 = p2.getPiece();
	if (piece2 == 'J' || piece2 == 'j')
		piece2 = p1.getJokerRep();

	switch (piece1)
	{
	case 'R':
	case 'r':

		break;
	case 'P':
	case 'p':
		break;
	case 'S':
	case 's':
		break;
	case 'B':
	case 'b':
		break;
	case 'F':
	case 'f':
		break;
	default:
		return false;
	}
}

bool Game::gameInit()
{
	if (!initPlayersPtrs())
	{
		std::cout
			<< "could not initialize players, check command line argument. should be: <player1>-vs-<player2>. player1 and player2 can be either of file or auto.";
		return false;
	}

	player1->getInitialPositions(PLAYER1, player1Pieces); //initialize player1 pieces
	player2->getInitialPositions(PLAYER2, player2Pieces); //initialize player2 pieces

	bool player1InitialLegal = checkInitialLegalPieces(player1Pieces);
	bool player2InitialLegal = checkInitialLegalPieces(player2Pieces);

	if (player1InitialLegal && !player2InitialLegal)
	{
		// player1 initialization is legal, but player2 initialization is illegal
		declareWinner(PLAYER1);
		return false;
	}
	if (!player1InitialLegal && player2InitialLegal)
	{
		// player1 initialization is illegal, but player2 initialization is legal
		declareWinner(PLAYER2);
		return false;
	}
	if (!player1InitialLegal && !player2InitialLegal)
	{
		// both players initializations are illegal
		declareWinner(BOTH);
		return false;
	}
	initBoard();
	//check both players flag count
	// if any of the players dont have flags, and the other does, declare winner. if both lost all flags, declare tie

	return true;//board init completed, can start on getting player moves
}
