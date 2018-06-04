COMP = g++

EXE_OBJS = main.o AlgorithmRegistration.o BoardImpl.o PieceCounter.o \
Game.o TournamentManager.o

LIB_OBJS = RSPPlayer_204621304.o BoardImpl.o PieceCounter.o

LIBS = -ldl -pthread
LIB = libRSPPlayer_204621304.so

EXEC = ex3

CPP_COMP_FLAGS = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG \
-pthread

all: rps_lib rps_tournament

rps_tournament:$(EXEC)

rps_lib:$(LIB)



$(EXEC):$(EXE_OBJS)
	$(COMP) -rdynamic $(EXE_OBJS) $(LIBS) -o $@

$(LIB): $(LIB_OBJS)
	$(COMP) -shared -Wl,-soname,$(LIB) -o $(LIB) $(LIB_OBJS)

main.o: main.cpp TournamentManager.h PlayerAlgorithm.h Point.h \
 PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h \
 AlgorithmRegistration.h RandomGenerator.h Game.h BoardImpl.h PointImpl.h \
 PieceCounter.h FightInfoImpl.h PiecePositionImpl.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp -mcmodel=large

AlgorithmRegistration.o: AlgorithmRegistration.cpp \
 AlgorithmRegistration.h PlayerAlgorithm.h Point.h PiecePosition.h \
 Board.h FightInfo.h Move.h JokerChange.h TournamentManager.h \
 RandomGenerator.h Game.h BoardImpl.h PointImpl.h PieceCounter.h \
 FightInfoImpl.h PiecePositionImpl.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp -mcmodel=large

BoardImpl.o: BoardImpl.cpp BoardImpl.h Board.h Point.h PiecePosition.h \
 PointImpl.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp -mcmodel=large

PieceCounter.o: PieceCounter.cpp PieceCounter.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp -mcmodel=large

Game.o: Game.cpp Game.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h \
 FightInfo.h Move.h JokerChange.h BoardImpl.h PointImpl.h PieceCounter.h \
 FightInfoImpl.h PiecePositionImpl.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp -mcmodel=large

TournamentManager.o: TournamentManager.cpp TournamentManager.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h AlgorithmRegistration.h RandomGenerator.h Game.h \
 BoardImpl.h PointImpl.h PieceCounter.h FightInfoImpl.h \
 PiecePositionImpl.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp -mcmodel=large

RSPPlayer_204621304.o: RSPPlayer_204621304.cpp RSPPlayer_204621304.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h BoardImpl.h PointImpl.h PieceCounter.h PiecePositionImpl.h \
 RandomGenerator.h MoveImpl.h BoardSpot.h JokerChangeImpl.h \
 AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp -mcmodel=large

clean:
	rm -f $(EXE_OBJS) $(LIB_OBJS) $(EXEC) $(LIB)
