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

class TournamentManager {
public:
    TournamentManager(const TournamentManager&) = delete;
    TournamentManager(TournamentManager&&) = delete;



    static TournamentManager& getTournamentManager()
    {
        return theManager;
    }
    bool parseCommandLine(int argc, char** argv); // this method reads and parses the command line arguments
    bool loadPlayers(); // loads all the so's if there is only 1 so returns false


private:
    TournamentManager() = default;
    static TournamentManager theManager;

    bool setCWD();//sets the path to the current directory
    bool setThreads(const std::string& argVal);
    void registerAlgorithm(const std::string& id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod);

    friend class AlgorithmRegistration;

    std::string soPath;
    int totalThreads;

    std::map<std::string,std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory; //maps all player IDs to factory methods
    std::list<void*> libs; // save all the loaded so's in here

    std::vector<std::thread> workers;
    

};


#endif //TOURNAMENTMANAGER_TOURNAMENTMANAGER_H
