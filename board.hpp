#ifndef _BOARD__HPP
#define _BOARD__HPP
#include <vector>
#include <cstdio>
#include "gridinfo.hpp"
using std::vector;
using std::size_t;





class Board{
  //your implementation goes here
  vector<vector<GridInfo> > grids;
  size_t rows_num;
  size_t cols_num;
  size_t mine_num;
  void generate_mines();
  void recursive_update_board(size_t row_index, size_t col_index);
  void count_mine(size_t ro, size_t cl, int & answer);
  void initialize_mine_nums();
  void initialize_grids();
public:
  Board(size_t rows, size_t columns,size_t mine);
  void print_board(bool is_over);
  void board_on_click(size_t row_index, size_t col_index);
};





#endif
