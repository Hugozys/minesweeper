#include "gridinfo.hpp"
#include <iostream>

void GridInfo::print_grid_content_not_over(){
  if (has_clicked){
    std::cout<<mine_num_around;
  }
  else if (has_marked){
    std::cout<<"?";
  }
  else{
    std::cout<<" ";
  }
}


void GridInfo::print_grid_content_over(){
  if (is_mine){
    std::cout<<"*";
  }
  else{
    print_grid_content_not_over();
  }
}


void GridInfo::print_grid_content(bool is_over){
  if(is_over){
    print_grid_content_over();
  }
  else{
    print_grid_content_not_over();
  }
}

bool GridInfo::get_is_mine(){
  return is_mine;
}

void GridInfo::set_is_mine(bool to_set){
  is_mine = to_set;
}

bool GridInfo::get_has_clicked(){
  return has_clicked;
}

void GridInfo::set_has_clicked(bool to_set){
  has_clicked = to_set;
}

bool GridInfo::get_has_marked(){
  return has_marked;
}

void GridInfo::set_has_marked(bool to_set){
  has_marked = to_set;
}

int GridInfo::get_mine_num_around(){
  return mine_num_around;
}

void GridInfo::set_mine_num_around(int to_set){
  mine_num_around = to_set;
}
