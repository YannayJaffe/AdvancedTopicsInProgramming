cmake_minimum_required(VERSION 3.10)
project(dummyAlgorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(dummyAlgorithm main.cpp AlgorithmRegistration.h Board.h BoardImpl.h BoardImpl.cpp BoardSpot.h FightInfo.h FightInfoImpl.h JokerChange.h JokerChangeImpl.h Move.h MoveImpl.h PieceCounter.h PieceCounter.cpp PiecePosition.h PiecePositionImpl.h PlayerAlgorithm.h Point.h PointImpl.h RandomGenerator.h RSPPlayer_123456789.h RSPPlayer_123456789.cpp)