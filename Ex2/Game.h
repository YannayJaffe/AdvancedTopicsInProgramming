//
// Created by yanna on 05/07/18.
//

#ifndef EX2_GAME_H
#define EX2_GAME_H
// this class manages the game between the players
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include "PlayerAlgorithm.h"
#include "FilePlayerAlgorithm.h"
#include "AutoPlayerAlgorithm.h"
#include "Board.h"
#include "BoardImpl.h"


class Game
{
public:
    Game(int argc, char** argv); // provide the inputs from the command line in order to determine the game mode
    
    void runGame();

private:
    
    // note: add a win reason enum and print the win reason/add more arguments so a correct win reason can be outputted
    void declareWinner(int playerId) const; // this method is called when the game should end, and declares the winner.
    
    bool initPlayersPtrs(); // this method initializes the players unique_ptrs. returns false if could not init
    
    bool gameInit(); //this method performs all initialization and returns whether the game can continue or should be finished
    
    bool checkLegalPieces(
            const std::vector<std::unique_ptr<PiecePosition>>& playerPieces) const; //this method receives a vector of pieces, and determines if its legal
    
    
    enum class AlgoType
    {
        FILE, AUTO
    };
    
    static const int BOTH = 0;
    static const int PLAYER1 = 1;
    static const int PLAYER2 = 2;
    
    const int totalXVals = 10; //number of columns in the board (total x values)
    const int totalYVals = 10; // number of rows in the board (total y values)
    const int totalRocks = 2;
    const int totalPapers = 5; // total Papers
    const int totalScissors = 1; // total Scissors
    const int totalBombs = 2; // total Bombs
    const int totalJokers = 2; // total Jokers
    const int totalFlags = 1; // total Flags
    
    bool isLegalCommandLine;
    AlgoType player1Algo;
    AlgoType player2Algo;
    std::unique_ptr<PlayerAlgorithm> player1;
    std::unique_ptr<PlayerAlgorithm> player2;
    std::vector<std::unique_ptr<PiecePosition>> player1Pieces;
    std::vector<std::unique_ptr<PiecePosition>> player2Pieces;
    std::unique_ptr<Board> board;
    int totalMoves;
    
    
};


#endif //EX2_GAME_H
