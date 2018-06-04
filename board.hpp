#ifndef _BOARD__HPP
#define _BOARD__HPP
#include <vector>
#include <cstdio>
using std::vector;
using std::size_t;





class Board{
  //your implementation goes here
  vector<vector<GridInfo> > grids;
  size_t rows_num;
  size_t cols_num;
  size_t mine_num;
  void generate_mines();
public:
  Board(size_t rows, size_t columns);
  void print_board();
};





#endif
