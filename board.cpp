#include "board.hpp"
#include <iostream>
#include <set>
#include <utility>
#include <cstdlib>
#include "exception.hpp"
using std::set;
using std::pair;
const char * TOP_LEFT = "\u2554";
const char * TOP_MIDDLE = "\u2566";
const char * TOP_RIGHT = "\u2557";

const char * MID_LEFT = "\u2560";
const char * MID_MIDDLE = "\u256C";
const char * MID_RIGHT = "\u2563";

const char * BOT_LEFT = "\u255A";
const char * BOT_MIDDLE = "\u2569";
const char * BOT_RIGHT = "\u255D";

const char * HORI = "\u2550";
const char * VERT = "\u2551";


void Board::print_size_to_char(size_t index){
  if (index >=0 && index <= 9){
    std::cout<<index;
  }
  else{
    char value = 'A' + index - 10;
    std::cout<<value;
  }
}

size_t Board::char_to_size(char alphabet){
  if (alphabet >= '0' && alphabet <= '9'){
    return alphabet - '0';
  }
  if (alphabet >= 'a' && alphabet <= 't'){
    return alphabet - 'a' + 10;
  }
  if (alphabet >= 'A' && alphabet <= 'T'){
    return alphabet - 'A' + 10;
  }
  throw InvalidIndex();
}

void Board::parse_coordinate(std::stringstream & raw_stream, size_t & row_index, size_t & col_index){
  std::string row_str;
  std::string col_str;
  raw_stream >> row_str;
  raw_stream >> col_str;
  if (row_str.size() != 1 || col_str.size() != 1){
    throw InvalidIndex();
  }
  //0=> 48  9 => 57
  row_index =  char_to_size(row_str[0]);
  col_index =  char_to_size(col_str[0]);
  //a=> 97  A => 65
}



void Board::count_mine(size_t ro, size_t cl, int & answer){
  if (grids[ro][cl].get_is_mine()){
    ++answer;
  }
}
void Board::initialize_mine_nums(){
  for (size_t i = 0; i < rows_num; ++i){
    for (size_t j = 0; j < cols_num; ++j){
      if (grids[i][j].get_is_mine()){
	continue;
      }
      else{
	int answer = 0;
	if (i > 0){  //up
	  count_mine(i-1,j,answer);
	}
	if (i < rows_num - 1){ //down
	  count_mine(i+1,j,answer);
	}
	if (j > 0){ //left
	  count_mine(i,j-1,answer);
	}
	if (j < cols_num - 1){ //right
	  count_mine(i,j+1,answer);
	}
	if (i > 0 && j > 0){ //left-up
	  count_mine(i-1,j-1,answer);
	}
	if (i > 0 && j < cols_num - 1){ //right-up
	  count_mine(i-1,j+1,answer);
	}
	if (i < rows_num - 1 && j < cols_num - 1){ //right-down
 	  count_mine(i+1,j+1,answer);
	}
	if (i < rows_num - 1 && j > 0){ //left-down
	  count_mine(i+1,j-1,answer);
	}
	grids[i][j].set_mine_num_around(answer);
      }
    }
  }
}

void Board::initialize_grids(){
  set<pair<size_t, size_t> > unique_mine_coord_set;
  for (size_t i = 0; i < mine_num; ++i){
    size_t ro; 
    size_t cl;
    pair<size_t,size_t> temp;
    do{
      ro = rand() % rows_num;
      cl = rand() % cols_num;
      temp = std::make_pair(ro,cl);
    }while(unique_mine_coord_set.find(temp) != unique_mine_coord_set.end());
    unique_mine_coord_set.insert(std::make_pair(ro,cl));
    grids[ro][cl].set_is_mine(true);
  }
  initialize_mine_nums();
}


Board::Board(size_t rows, size_t columns,size_t mine):grids(vector<vector<GridInfo> >(rows, vector<GridInfo>(columns))),rows_num(rows),cols_num(columns),mine_num(mine),to_win_num(rows*columns - mine){
  initialize_grids();
  initialize_mine_nums();
}


void Board::print_board(bool is_over){
  std::cout<<" ";
  for (size_t index = 0; index < cols_num; ++index){
    std::cout<<" "<<" ";
    print_size_to_char(index);
    std::cout<<" ";
  }
  std::cout<<std::endl;
  for (size_t i = 0; i < 2*rows_num+1; ++i){
    for (size_t j = 0; j < cols_num + 1; ++j){
      if (i == 0){
	if (j == 0){
	  std::cout<<" "<<TOP_LEFT<<HORI<<HORI<<HORI;
	}
	else if (j == cols_num){
	  std::cout<<TOP_RIGHT<<std::endl;
	}
	else{
	  std::cout<<TOP_MIDDLE<<HORI<<HORI<<HORI;
	}
      }
      else if(i == 2*rows_num){
	if (j == 0){
	  std::cout<<" "<<BOT_LEFT<<HORI<<HORI<<HORI;
	}
	else if (j == cols_num){
	  std::cout<<BOT_RIGHT<<std::endl;
	}
	else{
	  std::cout<<BOT_MIDDLE<<HORI<<HORI<<HORI;
	}
      }
      else{
	if (j == 0 && i % 2 == 0){
	  std::cout<<" "<<MID_LEFT<<HORI<<HORI<<HORI;
	}
	else if (j == cols_num  && i % 2 == 0){
	  std::cout<<MID_RIGHT<<std::endl;
	}
	else if (j == cols_num && i % 2 != 0){
	  std::cout<<VERT<<std::endl;
	}
	else if (j == 0 && i % 2 != 0){
	  print_size_to_char(i/2);
	  std::cout<<VERT<<" ";
	  grids[i/2][j].print_grid_content(is_over);
	  std::cout<<" ";
	}
	else if (i % 2 != 0){
	  std::cout<<VERT<<" ";
	  grids[i/2][j].print_grid_content(is_over);
	  std::cout<<" ";
	  //grids[i/2][j]<<" ";
	} 
	else{
	  std::cout<<MID_MIDDLE<<HORI<<HORI<<HORI;
	}
      }
    }
  }
}


bool Board::isValidIndex(int row, int col){
  int row_size = static_cast<int>(rows_num);
  int col_size = static_cast<int>(cols_num);
  return row >= 0 && row < row_size && col >=0 && col <  col_size;		 
}
void Board::recursive_update_board(size_t row_index, size_t col_index){
  //if this grid is mine or has been clicked, we stop and return
  if (grids[row_index][col_index].get_is_mine() || grids[row_index][col_index].get_has_clicked()){
    return;
  }
  else{
    grids[row_index][col_index].set_has_clicked(true);
    grids[row_index][col_index].set_has_marked(false);
    --to_win_num;
  //else we change this grid's status to has_clicked,unset mark
    if (grids[row_index][col_index].get_mine_num_around() == 0){
      int next_steps[8][2]= {{0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1}}; //check 8 cells around
      for (int i = 0; i < 8; ++i){
	int next_row_ind = row_index + next_steps[i][0];
	int next_col_ind = col_index + next_steps[i][1];
	if (isValidIndex(next_row_ind, next_col_ind)){
	  recursive_update_board(next_row_ind, next_col_ind);
	}
      }
    }
  }
}

void Board::board_on_click(size_t row_index, size_t col_index){
  if (row_index >= rows_num || col_index >= cols_num || row_index < 0 || col_index < 0){
    throw IndexOutOfBound();
  }
  else if(grids[row_index][col_index].get_is_mine()){
    throw GameOver(false);
  }
  else if(grids[row_index][col_index].get_has_clicked()){
    throw RedundantClick();
  }
  else{
    recursive_update_board(row_index, col_index);
  }
}




void Board::board_on_mark(size_t row_index, size_t col_index){
  if (row_index >= rows_num || col_index >= cols_num || row_index < 0 || col_index < 0){
    throw IndexOutOfBound();
  }
  else if(grids[row_index][col_index].get_has_clicked()){
    throw RedundantMark();
  }
  else if (grids[row_index][col_index].get_has_marked()){
    grids[row_index][col_index].set_has_marked(false);
  }
  else{
    grids[row_index][col_index].set_has_marked(true);
  }						    
}

bool Board::has_won(){
  return (to_win_num == 0);
}

