.PHONY: clean
CXX = g++
CPPFLAGS = -std=gnu++11 -Wall -Werror -pedantic
DEBUG = -ggdb3
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

test_board: $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<



clean:
	rm -f *~ *# *.o
