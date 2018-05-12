//
// Created by yanna on 05/07/18.
//

#include "Game.h"

Game::Game(int argc, char** argv) : player1Algo(AlgoType::FILE), player2Algo(AlgoType::FILE), player1(nullptr), player2(nullptr), board(nullptr),
                                    totalMoves(0)
{
    if (argc < 2)
    {
        isLegalCommandLine = false;
    } else
    {
        isLegalCommandLine = true;
        std::string commandLine(argv[2]);
        if (commandLine.compare("auto-vs-file") == 0)
        {
            player1Algo = AlgoType::AUTO;
            player2Algo = AlgoType::FILE;
            
        } else if (commandLine.compare("file-vs-auto") == 0)
        {
            player1Algo = AlgoType::FILE;
            player2Algo = AlgoType::AUTO;
            
        } else if (commandLine.compare("auto-vs-auto") == 0)
        {
            player1Algo = AlgoType::AUTO;
            player2Algo = AlgoType::AUTO;
        } else if (commandLine.compare("file-vs-file") == 0)
        {
            player1Algo = AlgoType::FILE;
            player2Algo = AlgoType::FILE;
            
        } else
        {
            isLegalCommandLine = false;
        }
    }
    board = std::make_unique<BoardImpl>(totalXVals,totalYVals);
    
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
