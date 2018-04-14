#include "Match.h"


int main()
{
    const std::string player1Board("player1.rps_board");
    const std::string player2Board("player2.rps_board");
    const std::string player1Moves("player1.rps_moves");
    const std::string player2Moves("player2.rps_Moves");
    Match match(player1Board, player2Board, player1Moves, player2Moves);
    match.loadBoard();
    match.printInitErrors(std::cout);
    match.playMoves();
    match.printMoveErrors(std::cout);
    match.printWinner(std::cout);
    return 0;
}