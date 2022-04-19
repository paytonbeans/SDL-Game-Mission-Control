#ifndef obj_node_h
#define obj_node_h


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "gameObject.h"
#include <string>


class obj_node{

public:

  void node_init(gameObject * obj, std::string t);
  void node_del();


  gameObject* get_data();
  void set_next(obj_node* point);
  void set_prev(obj_node* point);
  std::string get_type();

  obj_node* get_next();
  obj_node* get_prev();

private:

  std::string type;
  obj_node * next;
  obj_node * prev;
  gameObject * data;




};

#endif
