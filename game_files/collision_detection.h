#ifndef collision_detection_h
#define collision_detection_h


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "gameObject.h"
#include "obj_node.h"
#include "collision_handler.h"


class collision_detection{

public:

  void collision_init(collision_handler * h);
  void reg_obj(gameObject * obj, std::string type);
  void unreg_obj(gameObject * obj);
  void check_collision();


private:

  obj_node * header;
  obj_node * tail;
  collision_handler * handler;

};

#endif
