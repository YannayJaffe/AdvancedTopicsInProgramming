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
        //game was finished because could not initialize
        return;
    }
    // in here we have both of the players piece vectors initialized and valid
    
    
}

bool Game::checkLegalPieces(const std::vector<std::unique_ptr<PiecePosition>>& playerPieces) const
{
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
    
    bool player1InitialLegal = checkLegalPieces(player1Pieces);
    bool player2InitialLegal = checkLegalPieces(player2Pieces);
    
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
    
    
    return true;
}
