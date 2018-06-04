#include <iostream>
#include "TournamentManager.h"

int main(int argc, char **argv)
{
    auto &tournamentManager = TournamentManager::getTournamentManager();

    if (!tournamentManager.parseCommandLine(argc, argv))
        return -1;
    if (!tournamentManager.loadPlayers())
        return -1;


    tournamentManager.runTournament();

    tournamentManager.printScoreBoard();

    return 0;

}