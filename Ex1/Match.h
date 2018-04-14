#ifndef EX1_MATCH_H
#define EX1_MATCH_H

#include <string>
#include <ostream>
#include "Player.h"
#include "GameBoardForPlayers.h"

class Match
{
public:
    Match(const std::string& player1Board, const std::string& player2Board, const std::string& player1Moves, const std::string& player2Moves);
    void loadBoard();
    void printInitErrors(std::ostream& os);
    void playMoves();
    void printMoveErrors(std::ostream& os);
    void printWinner(std::ostream& os);
    void printBoard(std::ostream& os);
private:
    void checkFlags();
    
    std::string player1Board;
    std::string player2Board;
    std::string player1Moves;
    std::string player2Moves;
    
    GameBoardForPlayers board;
    Player player1;
    Player player2;
    
    int winner;
    int player1BadLineInit;
    int player2BadLineInit;
    std::string endMatchReason;
    
    bool matchFinished;
    bool openedInitFiles;
    bool openedMoveFiles;
    
};


#endif //EX1_MATCH_H
