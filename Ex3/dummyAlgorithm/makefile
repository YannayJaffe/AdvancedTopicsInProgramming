COMP = g++
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
LIB = libRSPPlayer_123456789.so
OBJS = RSPPlayer_123456789.o BoardImpl.o PieceCounter.o

rps_lib:$(LIB)

$(LIB): $(OBJS)
	$(COMP) -shared -Wl,-soname,$(LIB) -o $(LIB) $(OBJS)

RSPPlayer_123456789.o: RSPPlayer_123456789.cpp RSPPlayer_123456789.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h BoardImpl.h PointImpl.h PieceCounter.h PiecePositionImpl.h \
 RandomGenerator.h MoveImpl.h BoardSpot.h JokerChangeImpl.h \
 AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp -mcmodel=large

BoardImpl.o: BoardImpl.cpp BoardImpl.h Board.h Point.h PiecePosition.h \
 PointImpl.h
	 $(COMP) $(CPP_COMP_FLAG) -c $*.cpp -mcmodel=large

PieceCounter.o: PieceCounter.cpp PieceCounter.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp -mcmodel=large

clean:
	rm -f $(OBJS) $(LIB)
