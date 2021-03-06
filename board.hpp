#ifndef _BOARD__HPP
#define _BOARD__HPP
#include <vector>
#include <cstdio>
#include "gridinfo.hpp"
#include "sstream"
using std::vector;
using std::size_t;

class Board{
  //your implementation goes here
  vector<vector<GridInfo> > grids;
  size_t rows_num;
  size_t cols_num;
  size_t mine_num;
  size_t to_win_num;
  void generate_mines();
  void recursive_update_board(size_t row_index, size_t col_index);
  void count_mine(size_t ro, size_t cl, int & answer);
  void initialize_mine_nums();
  void initialize_grids();
  static size_t char_to_size(char alphabet);
  static void print_size_to_char(size_t index);
  bool isValidIndex(int row, int col);
public:
  static void parse_coordinate(std::stringstream & raw_stream, size_t & row_index, size_t & col_index);
  Board(size_t rows, size_t columns,size_t mine);
  void print_board(bool is_over);
  void board_on_click(size_t row_index, size_t col_index);
  void board_on_mark(size_t row_index, size_t col_index);
  bool has_won();
};

#endif
