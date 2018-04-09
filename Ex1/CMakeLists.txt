cmake_minimum_required(VERSION 3.10)
project(Ex1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ex1 main.cpp GameBoard.cpp GameBoard.h GamePiece.cpp GamePiece.h GeneralDefinitions.h Player.cpp Player.h GameBoardForPlayers.cpp GameBoardForPlayers.h GameMove.cpp GameMove.h MoveFactory.cpp MoveFactory.h)