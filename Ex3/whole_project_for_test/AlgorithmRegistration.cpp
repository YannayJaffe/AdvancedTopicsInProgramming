//
// Created by yannay on 04/06/18.
//
#include "AlgorithmRegistration.h"

AlgorithmRegistration::AlgorithmRegistration(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod)
{
TournamentManager::getTournamentManager().registerAlgorithm(id,factoryMethod);
}
