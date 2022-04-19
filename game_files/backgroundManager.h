#ifndef bck_Mngr_h
#define bck_Mngr_h

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "textureLoader.h"
#include <iostream>


class backgroundManager{

  public:
    void init(SDL_Renderer* ren, textureLoader* texture_loader);
    void update_background(int x);


  private:

    int last_pos;
    int length;

    SDL_Texture* layer1;
    SDL_Rect src_rect1;
    int layer1_scale;

    SDL_Texture* layer2;
    SDL_Rect src_rect2;
    int layer2_scale;

    SDL_Texture* layer3;
    SDL_Rect src_rect3;
    int layer3_scale;

    SDL_Rect dest_rect;

    textureLoader *t_loader;


    SDL_Renderer* obj_renderer;


};

#endif
