#include "Match.h"
#include <fstream>

int main()
{
    const std::string player1Board("player1.rps_board");
    const std::string player2Board("player2.rps_board");
    const std::string player1Moves("player1.rps_moves");
    const std::string player2Moves("player2.rps_Moves");
    const std::string outputFileName("rps.output");
    std::ofstream ofs;
    ofs.open(outputFileName);
    Match match(player1Board, player2Board, player1Moves, player2Moves);
    match.loadBoard();
    match.printInitErrors(std::cout);
    match.playMoves();
    match.printMoveErrors(std::cout);
    match.printWinner(ofs);
    ofs.flush();
    ofs.close();
    return 0;
}