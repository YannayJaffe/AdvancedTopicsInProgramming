cmake_minimum_required(VERSION 3.10)
project(TournamentManager)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic")

add_executable(TournamentManager main.cpp TournamentManager.cpp TournamentManager.h PlayerAlgorithm.h AlgorithmRegistration.h AlgorithmRegistration.cpp)

target_link_libraries(TournamentManager dl)

