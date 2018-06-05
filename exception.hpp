#ifndef _EXCEPTION__HPP
#define _EXCEPTION__HPP
#include <exception>

class IndexOutOfBound: public std::exception{
public:
  virtual const char * what() const noexcept(true){
    return "Invalid row/column index";
  }

};

class GameOver: public std::exception{
public:
  virtual const char * what() const noexcept(true){
    return "You picked a mine grid! You lose!!!";
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



#endif
