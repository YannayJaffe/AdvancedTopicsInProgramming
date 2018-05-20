cmake_minimum_required(VERSION 3.10)
project(Ex2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ex2 main.cpp AutoPlayerAlgorithm.cpp AutoPlayerAlgorithm.h Board.h BoardImpl.cpp BoardImpl.h FightInfo.h FightInfoImpl.h FilePlayerAlgorithm.cpp FilePlayerAlgorithm.h Game.cpp Game.h JokerChange.h Move.h PieceCounter.cpp PieceCounter.h PiecePosition.h PlayerAlgorithm.h Point.h PointImpl.h PiecePositionImpl.h MoveImpl.h JokerChangeImpl.h RandomGenerator.h BoardSpot.h)