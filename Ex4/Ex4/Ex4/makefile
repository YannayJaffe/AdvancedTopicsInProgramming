COMP = g++-5.3.0
OBJS = main.o

EXEC = ex4
CPP_COMP_FLAGS = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@

main.o: main.cpp ex4_header.h unit_test_util.h GameBoard.h
	$(COMP) $(CPP_COMP_FLAGS) -c $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)
