#include<iostream>
#include "board.hpp"
#include "exception.hpp"
#include <limits>
#include <getopt.h>
#include <sstream>
#include <iomanip>
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
void AsterickGenerator(int num){
  for(int i = 0; i< num; ++i){
    std::cout<<"*";
  }
  std::cout<<std::endl;
}

void print_help_message(){
  AsterickGenerator(70);
  std::cout<<"*Welcome to Hugo's terminal-based minesweeper! The goal of the game  *\n";
  std::cout<<"*is to uncover all the squares that do not contain mines without     *\n";
  std::cout<<"*being \"blown up\" by clicking on a square with a mine underneath.    *\n";
  std::cout<<"*The location of the mines is discovered by a process of logic.      *\n";
  std::cout<<"*Clicking on the game board will reveal what is hidden underneath    *\n";
  std::cout<<"*the chosen square or squares (a large number of blank squares may be*\n";
  std::cout<<"*revealed in one go if they are adjacent to each other).Some squares *\n";
  std::cout<<"*are blank but some contain numbers (1 to 8), each number being the  *\n";
  std::cout<<"*number of mines adjacent to the uncovered square. To help avoid     *\n";
  std::cout<<"*hitting a mine, the location of a suspected mine can be marked by   *\n";
  std::cout<<"*flagging it with the right mouse button. The game is won once all   *\n";
  std::cout<<"*blank squares have been uncovered without hitting a mine, any       *\n";
  std::cout<<"*remaining mines not identified by flags being automatically flagged *\n";
  std::cout<<"*by the computer. However, in the event that a game is lost and the  *\n";
  std::cout<<"*player mistakenly flags a safe square, that square will either      *\n";
  std::cout<<"*appear with a red X covering the mine (denoting it as safe), or     *\n";
  std::cout<<"*just a red X (also denoting it as safe). The game board comes in    *\n"; 
  std::cout<<"*three set sizes: beginner, intermediate, and expert, though a custom*\n";
  std::cout<<"*option is available as well.                                        *\n";
  std::cout<<"*            --https://en.wikipedia.org/wiki/Minesweeper_(video_game)*\n";
  AsterickGenerator(70);
  std::cout<<"NOTE: The row will be indexed via 0-9, if you create a board with row "<<std::endl;
  std::cout<<"      number larger than that, it will indexed via alphabet, starting "<<std::endl; 
  std::cout<<"      from A while the maximum is T. Same works for the column"<<std::endl<<std::endl;
  std::cout<<"Usage:\n\t./minesweeper <rows number> <columns number> <mine numbers>."<<std::endl;
  std::cout<<"Option:"<<std::endl;
  std::cout<<"\t"<<std::left<<std::setw(30)<<"-h/--help"<<"show this help message"<<std::endl;
  std::cout<<"Commands:"<<std::endl;
  std::cout<<"\t"<<std::left<<std::setw(30)<<"c <row> <column>"<<"explore this grid(case insensitive)"<<std::endl;
  std::cout<<"\t"<<std::left<<std::setw(30)<<"m <row> <column>"<<"mark this grid(case insensitive) if it's unexplored, unmark it if it's alread marked"<<std::endl;
  std::cout<<"\t"<<std::left<<std::setw(30)<<"q"<<"quit the game"<<std::endl;
  std::cout<<"\t"<<std::left<<std::setw(30)<<"b"<<"if you are playing an instance of the game, return to the main menu to select difficulty"<<std::endl;
  std::cout<<"\t"<<std::left<<std::setw(30)<<"easy"<<"play easy difficulty"<<std::endl;
  std::cout<<"\t"<<std::left<<std::setw(30)<<"intermediate"<<"play intermediate difficulty"<<std::endl;
  std::cout<<"\t"<<std::left<<std::setw(30)<<"expert"<<"play expert difficulty"<<std::endl;
  std::cout<<"\t"<<std::left<<std::setw(30)<<"customize"<<"customize your own board and mine numbers"<<std::endl;
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
