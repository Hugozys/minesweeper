.PHONY: clean depend
CXX = g++
CPPFLAGS = -std=gnu++11 -Wall -Werror -pedantic
DEBUG = -ggdb3
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

minesweeper: $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(DEBUG) -c $<

depend:
	makedepend $(SRCS)

clean:
	rm -f *~ *# *.o minesweeper
# DO NOT DELETE

gridinfo.o: gridinfo.hpp
board.o: board.hpp gridinfo.hpp exception.hpp
minesweeper.o: board.hpp gridinfo.hpp exception.hpp
