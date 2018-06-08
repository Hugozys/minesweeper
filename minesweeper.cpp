#include<iostream>
#include "board.hpp"
#include "exception.hpp"
#include <limits>
#include <getopt.h>
#include <sstream>
const int MAX_ROWS_COLS = 30;
const int EASY_ROWS_COLS = 8;
const int EASY_MINES = 10;
const int MED_ROWS_COLS = 16;
const int MED_MINES = 40;
const int HARD_ROWS_COLS = 24;
const int HARD_MINES = 99;
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
    Board::parse_coordinate(raw_stream,row_index,col_index);
    game_board.board_on_click(row_index, col_index);
    if (game_board.has_won()){
      throw GameOver(true);
    }
  }
  else if (command == "m"){
    Board::parse_coordinate(raw_stream, row_index,col_index);
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
  if (rows_num <= 0 || cols_num <= 0 || mine_num <=0 || rows_num > MAX_ROWS_COLS || cols_num > MAX_ROWS_COLS){
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
  catch (const std::exception & e){
    throw;
  }
}

void customize_game(size_t & row_nums, size_t & col_nums, size_t & mine_nums){
  std::cout<<"Enter row numbers  column numbers and mine numbers, separated by whitespace:"<<std::endl;
  std::string answer;
  std::stringstream raw_stream;
  std::string raw_string;
  int temp_row, temp_col, temp_mine = -1;
  getline(std::cin, raw_string, '\n');
  if (raw_string == "q"){
    throw QuitGame();
  }
  raw_stream << raw_string;
  raw_stream >> temp_row >> temp_col >> temp_mine;
  if (temp_row <= 0 || temp_col <= 0 || temp_mine <= 0 ||
      temp_row > MAX_ROWS_COLS || temp_col > MAX_ROWS_COLS){
    throw InvalidParameter();
  }
  if (temp_row * temp_col <= temp_mine){
    throw InvalidMineNum();
  }
  row_nums = (size_t) temp_row;
  col_nums = (size_t) temp_col;
  mine_nums = (size_t) temp_mine;
}


void choose_difficulty(size_t & row_nums, size_t & col_nums, size_t & mine_nums){
  std::string answer;
  std::stringstream raw_stream;
  std::string raw_string;
  getline(std::cin, raw_string, '\n');
  if (raw_string == "easy"){
    row_nums = col_nums = EASY_ROWS_COLS;
    mine_nums = EASY_MINES;
  }
  else if (raw_string == "intermediate"){
    row_nums = col_nums = MED_ROWS_COLS;
    mine_nums = MED_MINES;
  }
  else if (raw_string == "expert"){
    row_nums = col_nums = HARD_ROWS_COLS;
    mine_nums = HARD_MINES;
  }
  else if (raw_string == "customize"){
    try{
      customize_game(row_nums,col_nums,mine_nums);
    }
    catch (const std::exception & e){
      throw;
    }
  }
  else if (raw_string == "q"){
    throw QuitGame();
  }
  else{
    throw InvalidCommand();
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
      try{
	sanitize_input_arguments(argv);
      }
      catch (const std::exception & e){
	std::cout<<e.what()<<std::endl;
	return(EXIT_SUCCESS);
      }
      rows_num = atoi(argv[1]);
      cols_num = atoi(argv[2]);
      mine_num = atoi(argv[3]);
      first_time = false;
    }	
    else{
      std::cout<< "Please choose difficulty: easy(8 X 8, 10 mines), intermediate(16 X 16, 40 mines), Expert(24 X 24, 99 mines), Customize(maximum: 36 X 36)"<<std::endl;
      while(1){
	try{
	  choose_difficulty(rows_num, cols_num, mine_num);
	  break;
	}
	catch (const QuitGame & e){
	  return (EXIT_SUCCESS);
	}
	catch (const std::exception & e){
	  std::cout<<e.what()<<std::endl;
	  continue;
	}
      }
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
	catch (const QuitGame & e){
	  return (EXIT_SUCCESS);
	}
	catch (const ReturnMenu & e){
	  break;
	}
	catch (const GameOver & e){
	  game_board.print_board(true);
	  throw;
	}
	catch (const std::exception & e){
	  std::cout<<e.what()<<std::endl;
	  continue;
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
