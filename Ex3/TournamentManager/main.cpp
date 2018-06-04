#include <iostream>
#include "TournamentManager.h"
int main(int argc, char** argv ) {
    auto& tournamentManager = TournamentManager::getTournamentManager();

    tournamentManager.parseCommandLine(argc,argv);

    tournamentManager.loadPlayers();

    return 0;

}