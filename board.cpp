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


void Board::count_mine(size_t ro, size_t cl, int & answer){
  if (grids[ro][cl].get_is_mine()){
    ++answer;
  }
}
void Board::initialize_mine_nums(){
  for (size_t i = 0; i < rows_num; ++i){
    for (size_t j = 0; j < rows_num; ++j){
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


Board::Board(size_t rows, size_t columns,size_t mine):grids(vector<vector<GridInfo> >(rows, vector<GridInfo>(columns))),rows_num(rows),cols_num(columns),mine_num(mine){
  initialize_grids();
  initialize_mine_nums();
}


void Board::print_board(bool is_over){
  std::cout<<" ";
  for (size_t index = 0; index < cols_num; ++index){
    std::cout<<" "<<" "<<index<<" ";
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
	  std::cout<<i/2<<VERT<<" ";
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



void Board::recursive_update_board(size_t row_index, size_t col_index){
  //if this grid is mine or has clicked, we stop and return
  if (grids[row_index][col_index].get_is_mine() || grids[row_index][col_index].get_has_clicked()){
    return;
  }
  else{
    grids[row_index][col_index].set_has_clicked(true);
    grids[row_index][col_index].set_has_marked(false);
  //else we change this grid's status to has_clicked,unset mark
    if (grids[row_index][col_index].get_mine_num_around() == 0){
    //if row_index > 0
      if (row_index > 0){
	//investigate its up grid
	recursive_update_board(row_index - 1, col_index);
      }
      //if row_index < rows_num - 1
      if (row_index < rows_num - 1){
	//investigate its down grid
	recursive_update_board(row_index + 1, col_index);
      }
      //if col_index > 0
      if (col_index > 0){
	//investigate its left grid
	recursive_update_board(row_index, col_index - 1);
      }
      //if col_index < cols_num - 1
      if (col_index < cols_num - 1){
	//investiage its right grid
	recursive_update_board(row_index, col_index + 1);
      }
    }
  }
}

void Board::board_on_click(size_t row_index, size_t col_index){
  if (row_index >= rows_num || col_index >= cols_num || row_index < 0 || col_index < 0){
    throw IndexOutOfBound();
  }
  else if(grids[row_index][col_index].get_is_mine()){
    throw GameOver();
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


