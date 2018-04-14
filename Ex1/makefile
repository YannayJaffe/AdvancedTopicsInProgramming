COMP = g++-5.3.0
OBJS = main.o GameBoard.o GameBoardForPlayers.o GameInit.o \
GameMove.o GamePiece.o InitFactory.o Match.o \
MoveFactory.o PlayableFactory.o Player.o

EXEC = ex1
CPP_COMP_FLAGS = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@

main.o: main.cpp Match.h Player.h GeneralDefinitions.h \
 GameBoardForPlayers.h GameBoard.h GamePiece.h GameMove.h Playable.h \
 MoveFactory.h PlayableFactory.h InitFactory.h GameInit.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

GameBoard.o: GameBoard.cpp GameBoard.h GamePiece.h GeneralDefinitions.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

GameBoardForPlayers.o: GameBoardForPlayers.cpp GameBoardForPlayers.h \
 GameBoard.h GamePiece.h GeneralDefinitions.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

GameInit.o: GameInit.cpp GameInit.h Playable.h GeneralDefinitions.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

GameMove.o: GameMove.cpp GameMove.h GeneralDefinitions.h Playable.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

GamePiece.o: GamePiece.cpp GamePiece.h GeneralDefinitions.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

InitFactory.o: InitFactory.cpp InitFactory.h PlayableFactory.h Playable.h \
 GeneralDefinitions.h GameInit.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

Match.o: Match.cpp Match.h Player.h GeneralDefinitions.h \
 GameBoardForPlayers.h GameBoard.h GamePiece.h GameMove.h Playable.h \
 MoveFactory.h PlayableFactory.h InitFactory.h GameInit.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

MoveFactory.o: MoveFactory.cpp MoveFactory.h GameMove.h \
 GeneralDefinitions.h Playable.h PlayableFactory.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

PlayableFactory.o: PlayableFactory.cpp PlayableFactory.h Playable.h \
 GeneralDefinitions.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

Player.o: Player.cpp Player.h GeneralDefinitions.h GameBoardForPlayers.h \
 GameBoard.h GamePiece.h GameMove.h Playable.h MoveFactory.h \
 PlayableFactory.h InitFactory.h GameInit.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)
