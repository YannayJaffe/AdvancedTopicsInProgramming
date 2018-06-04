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
        std::cout<<"Not enough players, needed at least 2!" << std::endl;
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
    for (const auto &p:tempScoreBoard)
    {
        std::cout << p.first << " " << p.second.score << std::endl;
    }

}

void TournamentManager::runTournament()
{

}

void TournamentManager::runMatches()
{
    {
        std::lock_guard<std::mutex> lg(scoreBoardLock); // acquire lock

        //pick 2 players if any. if none are left, exit, if only one pick him and a random player, remember not to set score for the other player
        //update matches the players have played
        //if any of the players now played 30 matches, remove from unfinished list
    }//release lock

    // set up a game manager and both players
    // run match
    {
        std::lock_guard<std::mutex> lg(scoreBoardLock); // acquire lock
        //update scores
    }

}
