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
        libs.insert(libs.end(),dlib); // add the so to the list of so's
    }

    return false;
}
