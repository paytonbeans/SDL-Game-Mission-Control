#ifndef enemy_generator_h
#define enemy_generator_h

#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>
#include "gameObject.h"
#include "textureLoader.h"
#include "collision_detection.h"
#include "tileManager.h"
#include "obj_node.h"


class enemy_generator{

  public:
    void init(SDL_Renderer* ren, const char* graphic, textureLoader* t_loader, gameObject* player, collision_detection * col_d, int height, int width, double rate, int spawn_d, int speed, int turn_rate, bool wobble, int lifespan, int count);
    void update_enemy();
    void render_enemy();
    void reg_enemy(gameObject * obj, std::string type);
    void destroy_enemy(obj_node * obj);
    int get_survived();



  private:
    void spawn_enemy();

    SDL_Renderer *obj_renderer;
    SDL_Texture * sprite_sheet;
    SDL_Rect clips[4];

    collision_detection * collision;
    textureLoader * t_load;
    tileManager * t_mngr;

    const char * file;

    gameObject * target;
    int survived;
    int h;
    int w;
    double spawn_rate;
    int max_speed;
    int angular_speed;
    bool variance;
    int max_count;
    int lifetime;
    int spawn_delay;
    int count;





    obj_node * header_egen;
    obj_node * tail_egen;







};

#endif
