#ifndef collision_handler_h
#define collision_handler_h


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <string>
#include "particle_generator.h"
#include "gameObject.h"


class collision_handler{

public:

  void collision_handler_init(particle_generator * pg);
  void handle_collision(gameObject * obj_1, std::string type_1, gameObject * obj_2, std::string type_2);
  void player_boundry_collision(gameObject * p, gameObject * b);
  void player_ENEMY_collision(gameObject * p, gameObject * e);
  void enemy_boundry_collision(gameObject * e, gameObject * b);
  bool is_dead();


private:

  gameObject * player;
  gameObject * boundry;
  gameObject * enemy;
  particle_generator * p_gen;

  bool dead;


};

#endif
