cmake_minimum_required(VERSION 3.10)
project(Ex2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ex2 main.cpp Game.cpp Game.h FilePlayerAlgorithm.cpp FilePlayerAlgorithm.h AutoPlayerAlgorithm.cpp AutoPlayerAlgorithm.h Board.h FightInfo.h JokerChange.h Move.h PiecePosition.h PlayerAlgorithm.h Point.h BoardImpl.cpp BoardImpl.h)