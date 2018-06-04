#include "board.hpp"
#include <iostream>
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

Board::Board(int rows, int columns):grids(vector<vector<int> >(rows, vector<int>(columns, 0))),rows_num(rows),cols_num(columns){}



void Board::print_board(){
  for (size_t i = 0; i < 2*rows_num+1; ++i){
    for (size_t j = 0; j < cols_num; ++j){
      if (i == 0){
	if (j == 0){
	  std::cout<<TOP_LEFT<<HORI<<HORI<<HORI;
	}
	else if (j == cols_num - 1){
	  std::cout<<TOP_RIGHT<<std::endl;
	}
	else{
	  std::cout<<TOP_MIDDLE<<HORI<<HORI<<HORI;
	}
      }
      else if(i == 2*rows_num){
	if (j == 0){
	  std::cout<<BOT_LEFT<<HORI<<HORI<<HORI/*<<grids[i][j]*/;
	}
	else if (j == cols_num - 1){
	  std::cout<<BOT_RIGHT<<std::endl;
	}
	else{
	  std::cout<<BOT_MIDDLE<<HORI<<HORI<<HORI/*<<grids[i][j]*/;
	}
      }
      else{
	if (j == 0 && i % 2 == 0){
	  std::cout<<MID_LEFT<<HORI<<HORI<<HORI;
	}
	else if (j == cols_num - 1 && i % 2 == 0){
	  std::cout<<MID_RIGHT<<std::endl;
	}
	else if (j == cols_num - 1 && i % 2 != 0){
	  std::cout<<VERT<<std::endl;
	}
	else if (i % 2 != 0){
	  std::cout<<VERT<<" "<<grids[i/2][j]<<" ";
	} 
	else{
	  std::cout<<MID_MIDDLE<<HORI<<HORI<<HORI;
	}
      }
    }
  }
}
