//
// Created by yannay on 04/06/18.
//

#include <cstring>
#include "TournamentManager.h"

TournamentManager TournamentManager::theManager;

bool TournamentManager::parseCommandLine(int argc, char **argv)
{
    auto printIllegal = []()
    { std::cout << "illegal arguments. use -threads or -path or both" << std::endl; };
    switch (argc)
    {
        case 1:
        {
            totalThreads = 4;
            return setCWD();
        }

        case 3:
        {
            std::string argName(argv[1]);
            std::string argVal(argv[2]);
            if (argName == std::string("-threads"))
            {
                if (!setThreads(argVal))
                    return false;

                return setCWD();
            } else if (argName == std::string("-path"))
            {
                soPath = argVal;
                totalThreads = 4;
                return true;
            } else
            {
                printIllegal();
                return false;
            }
        }
        case 5:
        {
            std::string arg1Name(argv[1]);
            std::string arg1Val(argv[2]);
            std::string arg2Name(argv[3]);
            std::string arg2Val(argv[4]);
            if (arg1Name == std::string("-threads") && arg2Name == std::string("-path"))
            {
                soPath = arg2Val;
                return setThreads(arg1Val);

            } else if (arg2Name == std::string("-threads") && arg1Name == std::string("-path"))
            {
                soPath = arg1Val;
                return setThreads(arg2Val);
            } else
            {
                printIllegal();
                return false;
            }
        }
        default:
        {
            printIllegal();
            return false;
        }
    }
}

bool TournamentManager::setCWD()
{
    char buff[1024]; // length of current working directory name
    if (getcwd(buff, 1024) == NULL)
    {
        std::cout << "couldnt get current working directory name" << std::endl;
        return false;
    }
    soPath = std::string(buff);
    return true;
}

bool TournamentManager::setThreads(const std::string &argVal)
{

    try
    {
        totalThreads = std::stoi(argVal);
    }
    catch (...)
    {
        std::cout << "illegal number of threads, using 4 threads..." << std::endl;
        totalThreads = 4;
    }
    if (totalThreads < 1)
    {
        std::cout << "use at least 1 thread!" << std::endl;
        return false;
    }
    return true;
}

void TournamentManager::registerAlgorithm(const std::string &id,
                                          std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod)
{
    if (id2factory.find(id) != id2factory.end())
    {
        std::cout << "player ID: " << id << " is already loaded, overwriting previous instance..." << std::endl;
    }
    id2factory[id] = factoryMethod;
    scoreBoard[id] = TournamentManager::PlayerInfo();
    unfinishedPlayers.push_back(id);
}

bool TournamentManager::loadPlayers()
{
    constexpr int BUFF_SIZE = 1024; // buffer size for all so's
    std::string commandStr = "ls " + soPath + "/*.so";
    char inBuff[BUFF_SIZE];
    FILE *dl;
    dl = popen(commandStr.c_str(), "r");
    if (!dl)
    {
        std::cout << "could not load players. check for bad path";
        return false;
    }
    void *dlib;
    while (fgets(inBuff, BUFF_SIZE, dl))
    {
        // trim off the whitespace
        char *ws = strpbrk(inBuff, " \t\n");
        if (ws) *ws = '\0';
        dlib = dlopen(inBuff, RTLD_NOW);
        if (dlib == NULL)
        {
            std::cout << "could not load so: " << inBuff << std::endl;
            return false;
        }
        libs.insert(libs.end(), dlib); // add the so to the list of so's
    }
    if (id2factory.size() < 2)
    {
        std::cout << "Not enough players, needed at least 2!" << std::endl;
        return false;
    }
    return true;
}

void TournamentManager::cleanResources()
{
    for (auto dl:libs)
    {
        //dlclose(dl);
    }
}

void TournamentManager::printScoreBoard()
{
    using Comparator =  std::function<bool(const std::pair<std::string, TournamentManager::PlayerInfo> &,
                                           const std::pair<std::string, TournamentManager::PlayerInfo> &)>;

    Comparator compFunc = [](const std::pair<std::string, TournamentManager::PlayerInfo> &p1,
                             const std::pair<std::string, TournamentManager::PlayerInfo> &p2)
    {
        return p1.second.score >= p2.second.score;
    };
    std::vector<std::pair<std::string, TournamentManager::PlayerInfo>> tempScoreBoard;
    for (const auto &p:scoreBoard)
    {
        tempScoreBoard.emplace_back(p);
    }

    std::sort(tempScoreBoard.begin(), tempScoreBoard.end(), compFunc);
    std::cout << "Score Board:" << std::endl;
    std::cout << "Player Id\tMatches Played\tScore" << std::endl;
    for (const auto &p:tempScoreBoard)
    {
        std::cout << p.first << "\t\t" << p.second.matchesPlayed << "\t\t\t" << p.second.score << std::endl;
    }

}

void TournamentManager::runTournament()
{
    for (int i = 0; i < totalThreads - 1; i++)
    {
        // set up all threads to run the matches
        workers.emplace_back([this]()
                             { this->runMatches(); });
    }
    runMatches(); // also run matches from this thread
    for (auto &t:workers)
    {
        if (t.joinable())
            t.join();
    }

}

void TournamentManager::runMatches()
{
    std::unique_ptr<PlayerAlgorithm> player1;
    std::unique_ptr<PlayerAlgorithm> player2;
    bool updateScoreForPlayer2;
    std::string player1Id;
    std::string player2Id;

    while (true)
    {
        {
            std::lock_guard<std::mutex> lg(scoreBoardLock); // acquire lock

            //pick 2 players if any. if none are left, exit.
            if (!choosePlayers(player1, player1Id, player2, player2Id, updateScoreForPlayer2))
                return;

            updateMatchesPlayed(player1Id,player2Id);
        }//release lock

        // set up a game manager and both players
        // run match
        {
            std::lock_guard<std::mutex> lg(scoreBoardLock); // acquire lock
            //update scores
        }
    }

}

bool TournamentManager::choosePlayers(std::unique_ptr<PlayerAlgorithm> &player1, std::string &player1Id,
                                      std::unique_ptr<PlayerAlgorithm> &player2, std::string &player2Id,
                                      bool &updateScoreForPlayer2)
{
    if (unfinishedPlayers.empty())
        return false;

    if (unfinishedPlayers.size() == 1)
    {
        player1Id = unfinishedPlayers.front();
        player1 = id2factory[player1Id]();
        updateScoreForPlayer2 = false;
        std::vector<std::string> tempPlayers;
        for (const auto &p:scoreBoard)
        {
            if (p.first != player1Id)
                tempPlayers.emplace_back(p.first);
        }
        player2Id = tempPlayers[rng.getRange(0, static_cast<int>(tempPlayers.size() - 1))];
        player2 = id2factory[player2Id]();
    } else
    {
        int player1Idx = rng.getRange(0, static_cast<int>(unfinishedPlayers.size()) - 1);
        std::vector<std::string> tempPlayers;

        auto itr = unfinishedPlayers.begin();
        for (int i = 0; i < unfinishedPlayers.size(); i++)
        {
            if (i != player1Idx)
            {
                tempPlayers.emplace_back(*itr);
            } else
            {
                player1Id = std::string(*itr);
            }
            itr++;
        }
        player2Id = tempPlayers[rng.getRange(0, static_cast<int>(tempPlayers.size() - 1))];
        player1 = id2factory[player1Id]();
        player2 = id2factory[player2Id]();
        updateScoreForPlayer2 = true;
    }
    return true;
}

void TournamentManager::updateMatchesPlayed(const std::string &player1Id, const std::string &player2Id)
{
    if (scoreBoard[player1Id].matchesPlayed < totalGames)
        scoreBoard[player1Id].matchesPlayed++;
    if (scoreBoard[player2Id].matchesPlayed < totalGames)
        scoreBoard[player2Id].matchesPlayed++;

    unfinishedPlayers.remove_if([this](const std::string &s) -> bool
                                { return this->scoreBoard[s].matchesPlayed >= totalGames; });
}
