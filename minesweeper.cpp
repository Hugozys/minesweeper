#include<iostream>
#include "board.hpp"
#include "exception.hpp"
#include <limits>
#include <getopt.h>
#include <sstream>
const char *OPTSTR = "h";
const option LONGOPTS[] = {
  {"help",no_argument,0,'h'},
  {0,0,0,0}
};

void parse_command(Board & game_board){
  //char command;
  size_t row_index;
  size_t col_index;
  std::stringstream raw_stream;
  std::string raw_string;
  std::string command;
  getline(std::cin, raw_string, '\n');
  raw_stream << raw_string;
  raw_stream >> command;
  //what if row_index is not a valid number ??
  if (command == "c"){
    raw_stream >>row_index;
    raw_stream >>col_index;
    game_board.board_on_click(row_index, col_index);
    if (game_board.has_won()){
      throw GameOver(true);
    }
  }
  else if (command == "m"){
    raw_stream >>row_index;
    raw_stream >>col_index;
    game_board.board_on_mark(row_index, col_index);
  }
  else if (command == "q"){
    throw QuitGame();
  }
  else if (command == "b"){ 
    throw ReturnMenu();
  }
  else{
    throw InvalidCommand();
  }
}
void print_help_message(){
  std::cout<<"help message!"<<std::endl;
}


void read_options(int argc, char ** argv){
  int longopts = -1;
  int result = getopt_long(argc,argv,OPTSTR,LONGOPTS, &longopts);
  switch (result){
  case 'h':
    print_help_message();
    exit(EXIT_SUCCESS);
  case -1:
    break; //no options found
  case '?': //unrecognized options
  default: //help couldn't have argument
    std::cout<<"Please use ./minesweeper --help or -h to see usage of the game."<<std::endl;
    exit(EXIT_SUCCESS);
  }
}

void check_number_positivity(char ** argv){
  int rows_num = -1;
  int cols_num = -1;
  int mine_num = -1;
  rows_num = atoi(argv[1]);
  cols_num = atoi(argv[2]);
  mine_num = atoi(argv[3]);
  if (rows_num <= 0 || cols_num <= 0 || mine_num <=0){
    throw InvalidParameter();
  }
  else if (mine_num >= rows_num*cols_num){
    throw InvalidMineNum();
  }
  else{
    return;
  }
}


void sanitize_input_arguments(char ** argv){
  try{
    check_number_positivity(argv);
  }
  catch (const InvalidParameter & e){
    std::cout<<e.what()<<std::endl;
    exit(EXIT_SUCCESS);
  }
  catch (const InvalidMineNum & e){
    std::cout<< e.what()<<std::endl;
    exit(EXIT_SUCCESS);
  }
}

int main(int argc, char** argv){
  bool first_time = true;
  size_t rows_num = 10;
  size_t cols_num = 10;
  size_t mine_num = 10;
  while(1){
    if (first_time){
      //read from the command line argument
      read_options(argc,argv);
      if (argc != 4){
	std::cout<<"Usage: ./minesweeper <rows number> <columns number> <mine numbers>."<< "\nUse ./minesweeper --help or -h if you want to learn how to play this game."<<std::endl;
	return(EXIT_SUCCESS);
      }
      sanitize_input_arguments(argv);
      rows_num = atoi(argv[1]);
      cols_num = atoi(argv[2]);
      mine_num = atoi(argv[3]);
      first_time = false;
    }	
    else{
      //ask for rows_num,cols_num,mine_num
      //ask for different level of difficulties or customization
      /*
      size_t rows_num = 10;
      size_t cols_num = 10;
      size_t mine_num = 10;
      */
    }
    std::cout<<"Initiate Game Board...\n";
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
	  //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	  continue;
	}
	catch (const GameOver & e){
	  game_board.print_board(true);
	  throw;
	}
	catch (const QuitGame & e){
	  return (EXIT_SUCCESS);
	}
	catch (const ReturnMenu & e){
	  break;
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
	else if(again == 'n'){
	  return(EXIT_SUCCESS);
	}
	else{
	  std::cout<<"Invalid Command. Please enter y or n"<<std::endl;
	}
      }
      continue;
    }
  }
}
