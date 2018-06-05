#ifndef _GRIDINFO__HPP
#define _GRIDINFO__HPP


class GridInfo{
  bool is_mine;
  bool has_clicked;
  bool has_marked; //they are mutual exclusive
  int  mine_num_around;
  void print_grid_content_over(); //game over
  void print_grid_content_not_over(); //game not over
public:
  bool get_is_mine();
  void set_is_mine(bool to_set);

  bool get_has_clicked();
  void set_has_clicked(bool to_set);

  bool get_has_marked();
  void set_has_marked(bool to_set);
  
  int get_mine_num_around();
  void set_mine_num_around(int to_set);


  void print_grid_content(bool is_over);
};









#endif
