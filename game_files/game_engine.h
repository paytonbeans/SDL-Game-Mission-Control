#ifndef game_engine_h
#define game_engine_h

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "gameObject.h"
#include "backgroundManager.h"
#include "tileManager.h"
#include "textureLoader.h"
#include "collision_detection.h"
#include "particle_generator.h"
#include "collision_handler.h"
#include "fontManager.h"
#include "UI.h"
#include "enemy_generator.h"




class game_engine{
public:

  void init();
  void HandleEvents();
  void updateMechanics(double time_del);
  void render();
  bool get_game_is_running();
  void quit();
  void display_score();

  int GAME_BOUND_LEFT_X = 0;
  int GAME_BOUND_RIGHT_X = 1280;
  int GAME_BOUND_UPPER_Y = 0;
  int GAME_BOUND_LOWER_Y = 720;



  bool is_running = true;

  //Subsystems
  SDL_Renderer * my_renderer;
  textureLoader * t_loader;
  gameObject * player;
  backgroundManager * bg_mngr;
  tileManager * tl_mngr;
  collision_detection * col_d;
  collision_handler * handler;
  particle_generator * p_gen;
  fontManager * font_m;
  fontManager * font_l;
  ui * interface;
  enemy_generator * e_gen;

  bool pause;
  bool game_over;

  SDL_Rect ground;






};
#endif
