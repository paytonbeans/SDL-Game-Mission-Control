#ifndef p_node_h
#define p_node_h


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "gameObject.h"
#include <string>


class particle{

public:

  void particle_init(int start_x, int start_y, int start_height, int start_width, int start_xvel, int start_yvel, int life_span, int t);
  void particle_del();



  int get_lifetime();
  void set_lifetime(int i);
  void set_next(particle* point);
  void set_prev(particle* point);
  int get_type();
  SDL_Rect * get_dest();
  int particle_get_x_vel();
  int particle_get_y_vel();
  void particle_set_y_vel(int yvel);

  void update_particle(int x, int y, int xvel, int yvel, int width, int height, int life_span);

  particle* get_next();
  particle* get_prev();

private:


  particle * next;
  particle * prev;
  SDL_Rect * dest;
  int lifetime;
  int x_vel;
  int y_vel;
  int type;




};

#endif
