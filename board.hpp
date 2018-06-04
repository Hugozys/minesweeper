#ifndef _BOARD__HPP
#define _BOARD__HPP
#include <vector>
#include <cstdio>
using std::vector;
using std::size_t;
class Board{
  //your implementation goes here
  vector<vector<int> > grids;
  size_t rows_num;
  size_t cols_num;
public:
  Board(int rows, int columns);
  void print_board();
};





#endif
