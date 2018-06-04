COMP = g++
OBJS = main.o AlgorithmRegistration.o BoardImpl.o PieceCounter.o TournamentManager.o
LIBS = -ldl
EXEC = ex3

CPP_COMP_FLAGS = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

rps_tournament:$(EXEC)

$(EXEC):$(OBJS)
	$(COMP) -rdynamic $(OBJS) $(LIBS) -o $@


main.o: main.cpp TournamentManager.h PlayerAlgorithm.h Point.h \
 PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h \
 AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

AlgorithmRegistration.o: AlgorithmRegistration.cpp \
 AlgorithmRegistration.h PlayerAlgorithm.h Point.h PiecePosition.h \
 Board.h FightInfo.h Move.h JokerChange.h TournamentManager.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

BoardImpl.o: BoardImpl.cpp BoardImpl.h Board.h Point.h PiecePosition.h \
 PointImpl.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

PieceCounter.o: PieceCounter.cpp PieceCounter.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

TournamentManager.o: TournamentManager.cpp TournamentManager.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)
