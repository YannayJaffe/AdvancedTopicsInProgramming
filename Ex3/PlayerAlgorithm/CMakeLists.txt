cmake_minimum_required(VERSION 3.10)
project(PlayerAlgorithm)

set(CMAKE_CXX_STANDARD 14)

add_library(PlayerAlgorithm SHARED library.cpp library.h AlgorithmRegistration.h RSPPlayer_204621304.h RSPPlayer_204621304.cpp BoardImpl.cpp BoardImpl.h BoardSpot.h FightInfo.h FightInfoImpl.h JokerChange.h JokerChangeImpl.h Move.h MoveImpl.h PieceCounter.cpp PieceCounter.h PiecePosition.h PiecePositionImpl.h PlayerAlgorithm.h Point.h PointImpl.h RandomGenerator.h)