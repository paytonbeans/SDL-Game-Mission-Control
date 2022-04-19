#ifndef t_loader_h
#define t_loader_h

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <iostream>


class textureLoader{

  public:
    void init(SDL_Renderer* ren);
    SDL_Texture* load_image(const char* graphic);


  private:

    SDL_Surface *imageSurface;
    SDL_Renderer *obj_renderer;



};

#endif
