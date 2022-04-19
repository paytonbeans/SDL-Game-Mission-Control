#ifndef gameObject_h
#define gameObject_h


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <string>
#include <cmath>
#include "playerSpriteManager.h"
#include "tileManager.h"


class gameObject{

public:

  void obj_init(const char* grpahic, SDL_Renderer* ren, textureLoader* texture_loader, int type, int start_x, int start_y, tileManager* t_mngr, int swidth, int sheight);
  void obj_update(double time_del);
  void obj_render();
  void obj_quit();
  void set_state(std::string new_state);

  int obj_get_vel();
  void obj_set_vel(int new_vel);

  double obj_get_angle();
  void obj_set_angle(double a);

  int obj_get_x();
  int obj_get_y();
  int obj_get_x_vel();
  int obj_get_y_vel();
  int obj_get_width();
  int obj_get_height();
  int obj_get_lifespan();

  void obj_set_lifespan(int time);

  int get_resource();


private:
  SDL_Renderer* obj_renderer;

  SDL_Texture* obj_graphic;
  SDL_Rect obj_rect;

  playerSpriteManager* spr_mngr;
  textureLoader* t_loader;

  tileManager* tl_mngr;

  int lifespan;

  int width;
  int height;

  int x_pos;

  int y_pos;

  int acc;
  int vel;

  int a_acc;
  int a_vel;

  double angle;
  double rads;

  std::string state;

  int GAME_BOUND_LEFT_X = 0;
  int GAME_BOUND_RIGHT_X = 1280;
  int GAME_BOUND_UPPER_Y = 720;
  int GAME_BOUND_LOWER_Y = 0;

  int resource;
  int resource_max;
  int min_consumption;
  int consumption_rate;
  int regen_delay;

};

#endif
