COMP = g++-5.3.0
OBJS = AutoPlayerAlgorithm.o BoardImpl.o FilePlayerAlgorithm.o \
Game.o main.o PieceCounter.o 

EXEC = ex2
CPP_COMP_FLAGS = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@

AutoPlayerAlgorithm.o: AutoPlayerAlgorithm.cpp AutoPlayerAlgorithm.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h BoardImpl.h PointImpl.h PieceCounter.h PiecePositionImpl.h \
 RandomGenerator.h MoveImpl.h BoardSpot.h JokerChangeImpl.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

BoardImpl.o: BoardImpl.cpp BoardImpl.h Board.h Point.h PiecePosition.h \
 PointImpl.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

FilePlayerAlgorithm.o: FilePlayerAlgorithm.cpp FilePlayerAlgorithm.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h PiecePositionImpl.h PointImpl.h JokerChangeImpl.h \
 MoveImpl.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

Game.o: Game.cpp Game.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h \
 FightInfo.h Move.h JokerChange.h FilePlayerAlgorithm.h \
 PiecePositionImpl.h PointImpl.h JokerChangeImpl.h MoveImpl.h \
 AutoPlayerAlgorithm.h BoardImpl.h PieceCounter.h RandomGenerator.h \
 BoardSpot.h FightInfoImpl.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

main.o: main.cpp Game.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h \
 FightInfo.h Move.h JokerChange.h FilePlayerAlgorithm.h \
 PiecePositionImpl.h PointImpl.h JokerChangeImpl.h MoveImpl.h \
 AutoPlayerAlgorithm.h BoardImpl.h PieceCounter.h RandomGenerator.h \
 BoardSpot.h FightInfoImpl.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

PieceCounter.o: PieceCounter.cpp PieceCounter.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)
