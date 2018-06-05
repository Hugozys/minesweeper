#include "board.hpp"
int main(void){
  Board test(10,10,10);
  test.print_board(true);
  test.board_on_click(3,3);
  test.print_board(false);
}
