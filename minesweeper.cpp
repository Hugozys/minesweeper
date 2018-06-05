#include<iostream>
#include "board.hpp"
#include "exception.hpp"
void parse_command(Board & game_board){
  char command;
  size_t row_index;
  size_t col_index;
  std::cin>>command>>row_index>>col_index;
  //what if row_index is not a valid number ??
  if (command == 'c'){
    game_board.board_on_click(row_index, col_index);
  }
  else if (command == 'm'){
    game_board.board_on_mark(row_index, col_index);
  }
  else if (command == 'q'){
    throw QuitGame();
  }
  else{
    throw InvalidCommand();
  }
}


int main(void){
  while(1){
    std::cout<<"Initiate Game Board...\n";
    size_t rows_num = 10;
    size_t cols_num = 10;
    size_t mine_num = 10;
    Board game_board(rows_num,cols_num,mine_num);
    game_board.print_board(false);
    std::cout<<"Waiting for player input...\n";
    try{
      while(1){
	try{
	  parse_command(game_board);
	  game_board.print_board(false);
	}
	catch(const IndexOutOfBound & e){
	  std::cout<<e.what()<<std::endl;
	  continue;
	}
	catch (const RedundantMark & e){
	  std::cout<<e.what()<<std::endl;
	  continue;
	}
	catch (const RedundantClick & e){
	  std::cout<<e.what()<<std::endl;
	  continue;
	}
	catch (const InvalidCommand & e){
	  std::cout<<e.what()<<std::endl;
	  continue;
	}
	catch (const GameOver & e){
	  game_board.print_board(true);
	  throw;
	}
      }
    }
    catch(const GameOver & e){
      std::cout<<e.what()<<std::endl;
      char again;
      while(1){
	std::cin >> again;
	if (again == 'y'){
	  break;
	}
	else{
	  return(EXIT_SUCCESS);
	}
      }
      continue;
    }
  }
}
