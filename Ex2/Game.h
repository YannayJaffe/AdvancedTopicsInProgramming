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
#include <fstream>
#include "PlayerAlgorithm.h"
#include "FilePlayerAlgorithm.h"
#include "AutoPlayerAlgorithm.h"
#include "Board.h"
#include "BoardImpl.h"
#include "PieceCounter.h"
#include "FightInfo.h"
#include "FightInfoImpl.h"
#include "PiecePosition.h"
#include "PiecePositionImpl.h"


bool operator>(const PiecePosition& p1, const PiecePosition& p2);

bool operator<(const PiecePosition& p1, const PiecePosition& p2);

bool operator==(const PiecePosition& p1, const PiecePosition& p2);

namespace WinReason
{
    enum class Reason
    {
        ILLEGAL_INIT, // bad initialization (bad piece position vector)
        NO_MORE_FLAGS_INIT, // no more flags after initialization
        ILLEGAL_MOVE, // tried to do an illegal move
        NO_MORE_FLAGS_MOVES, // took over the last remaining flag during a move
        MAX_MOVES_REACHED // played the total maximum moves
    };
}

class Game
{
public:
    Game(int argc, char** argv, const std::string& outFile); // provide the inputs from the command line in order to determine the game mode
    
    void runGame();

private:

// note: add a win reason enum and print the win reason/add more arguments so a correct win reason can be outputted
    void declareWinner(int winnerId, WinReason::Reason reason); // this method is called when the game should end, and declares the winner.
    
    bool initPlayersPtrs(); // this method initializes the players unique_ptrs. returns false if could not init
    
    bool gameInit(); //this method performs all initialization and returns whether the game can continue or should be finished
    
    bool checkInitialLegalPieces(
            const std::vector<std::unique_ptr<PiecePosition>>& playerPieces) const; //this method receives a vector of pieces, and determines if its legal. use only in initialization
    
    bool pointInBoard(const Point& p) const; // this method verifies that a point is within the board limits
    
    void initBoard(); // this method initializes the game board, conducts all fights, and updates the FightInfo vector
    
    void initPlayerOnBoard(int playerId); // this method initializes only the player whos id is playerId on the board (and conducts fights...)
    
    int getPieceCount(int playerId,
                      char pieceType); //counts the remaining pieces of specified type of the specified player. if asked for jokers, count jokers. else count also joker current type
    
    std::unique_ptr<PiecePosition>& getPlayerPiece(int playerId, const Point& point); // returns the wanted player piece, nullptr if not found
    std::unique_ptr<PiecePosition> nullPiecePosition = nullptr; // in order to return a nullptr and not throw exception from the above method
    std::unique_ptr<FightInfo> getFightInfo(const PiecePosition& player1Piece,
                                            const PiecePosition& player2Piece); // conducts the fight between the pieces and generates the FightInfo
    
    bool isLegalMove(const Move& move, int playerId); // checks if a move is legal
    
    bool isMovable(const PiecePosition& piece);//returns true if the piece can be moved
    
    bool isSingleStep(const Move& move); // this method returns true only when the move is one step up/down/left/right.
    
    std::unique_ptr<FightInfo>
    playMove(const Move& move, int playerId); //plays the move and updates player's piece vectors accordingly. returns the fight info
    
    bool doFullMove(int playerId); // this method performs an entire move. return true if a winner is not declared
    
    bool doJokerChange(int playerId,
                       const JokerChange& jokerChange); // this method performs a joker change by the player. return true for success, false for illegal joker change
    
    int
    winConditionFlags();// returns 1 if player 1 has flags and player 2 doesnt. returns 2 if player 2 has flags and player 1 doesnt. returns 0 if both players dont have flags. return -1 if both have flags
    
    void printBoard(std::ostream& os);
    
    enum class AlgoType
    {
        FILE, AUTO
    };
    
    static const int BOTH = 0;
    static const int NONE = 0;
    static const int PLAYER1 = 1;
    static const int PLAYER2 = 2;
    
    static const int totalXVals = 10; //number of columns in the board (total x values)
    static const int totalYVals = 10; // number of rows in the board (total y values)
    static const int totalRocks = 2; // total Rocks
    static const int totalPapers = 5; // total Papers
    static const int totalScissors = 1; // total Scissors
    static const int totalBombs = 2; // total Bombs
    static const int totalJokers = 2; // total Jokers
    static const int totalFlags = 1; // total Flags
    static const int maxMoves = 100; //maximum moves until a tie is declared
    
    
    bool isLegalCommandLine;
    AlgoType player1Algo;
    AlgoType player2Algo;
    std::unique_ptr<PlayerAlgorithm> player1;
    std::unique_ptr<PlayerAlgorithm> player2;
    std::vector<std::unique_ptr<PiecePosition>> player1Pieces; // an element could be nullptr
    std::vector<std::unique_ptr<PiecePosition>> player2Pieces; //an element could be nullptr
    BoardImpl board;
    std::vector<std::unique_ptr<FightInfo>> fights;
    int totalMoves;
    int player1Moves;
    int player2Moves;
    int player1Points;
    int player2Points;
    
    const std::string outFileName;
    
    
};


#endif //EX2_GAME_H
