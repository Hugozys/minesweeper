#ifndef _EXCEPTION__HPP
#define _EXCEPTION__HPP
#include <exception>

class IndexOutOfBound: public std::exception{
public:
  virtual const char * what() const noexcept(true){
    return "Invalid row/column index";
  }

};

class InvalidIndex: public std::exception{
public:
  virtual const char * what() const noexcept(true){
    return "row(column) must be [0-9]/[a-t]/[A-T]";
  }
};

class GameOver: public std::exception{
  bool has_won;
public:
  GameOver(bool w):has_won(w){}
  virtual const char * what() const noexcept(true){
    if (has_won){
      return "You explored all the grids without touching a mine! You win!!! Do you want to play again? (Press y for yes or n for no)";
    }
    return "You picked a mine grid! You lose!!! Do you want to play again? (Press y for yes or n for no)";
  }
};

class RedundantClick: public std::exception{
public:
  virtual const char * what() const noexcept(true){
    return "This grid has already been explored";
  }
  

};


class RedundantMark: public std::exception{
public:
  virtual const char * what() const noexcept(true){
    return "You could not mark a explored grid";
  }
  
};


class InvalidCommand: public std::exception{
public:
  virtual const char * what() const noexcept(true){
    return "Invalid command";
  }
  
};


class QuitGame: public std::exception{
  
};

class ReturnMenu: public std::exception{
};

class InvalidParameter: public std::exception{
public:
  virtual const char * what() const noexcept(true){
    return "rows number, columns number and mines number must be integers larger than 0.\nrows number and columns number must be less than or equal to 36";
  }
};

class InvalidMineNum: public std::exception{
public:
  virtual const char * what() const noexcept(true){
    return "mine numbers could not exceed or equal to the total grids";
  }
};  
#endif
