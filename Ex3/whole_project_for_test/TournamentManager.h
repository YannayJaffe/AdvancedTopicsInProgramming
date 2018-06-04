//
// Created by yannay on 04/06/18.
//

#ifndef TOURNAMENTMANAGER_TOURNAMENTMANAGER_H
#define TOURNAMENTMANAGER_TOURNAMENTMANAGER_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <map>
#include <functional>
#include <memory>
#include "PlayerAlgorithm.h"
#include "AlgorithmRegistration.h"
#include <list>
#include <cstring>
#include <dlfcn.h>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include "RandomGenerator.h"
#include "Game.h"

class TournamentManager
{
public:
    TournamentManager(const TournamentManager &) = delete;

    TournamentManager(TournamentManager &&) = delete;

    ~TournamentManager()
    {
        cleanResources();
    }

    static TournamentManager &getTournamentManager()
    {
        return theManager;
    }

    bool parseCommandLine(int argc, char **argv); // this method reads and parses the command line arguments
    bool loadPlayers(); // loads all the so's if there is only 1 so returns false

    void printScoreBoard(); // prints the scores in descending order

    void runTournament();



private:
    struct PlayerInfo
    {
        PlayerInfo() : matchesPlayed(0), score(0)
        {}

        int matchesPlayed;
        int score;
    };

    TournamentManager() = default;

    static TournamentManager theManager;


    bool setCWD();//sets the path to the current directory
    bool setThreads(const std::string &argVal);

    void registerAlgorithm(const std::string &id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod);

    void cleanResources();

    void runMatches();

    bool choosePlayers(std::unique_ptr<PlayerAlgorithm>& player1, std::string& player1Id, std::unique_ptr<PlayerAlgorithm>& player2, std::string& player2Id, bool& updateScoreForPlayer2);

    void updateMatchesPlayed(const std::string& player1Id, const std::string& player2Id);

    void updateScore(const std::string &player1Id, const std::string &player2Id, int result, bool updateScoreForPlayer2);

    friend class AlgorithmRegistration;

    static constexpr int totalGames = 30;
    static constexpr int pointsForWin = 3;
    static constexpr int pointsForTie = 1;

    std::string soPath;
    int totalThreads;

    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory; //maps all player IDs to factory methods
    std::list<void *> libs; // save all the loaded so's in here
    std::map<std::string,TournamentManager::PlayerInfo> scoreBoard;
    std::list<std::string> unfinishedPlayers; // a list of unfinished players
    RandomGenerator rng;

    std::vector<std::thread> workers;
    std::mutex scoreBoardLock;



};


#endif //TOURNAMENTMANAGER_TOURNAMENTMANAGER_H
