#ifndef plyrSprMngr_h
#define plyrSprMngr_h

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "textureLoader.h"


class playerSpriteManager{

  public:
    void init(const char* graphic, SDL_Renderer* ren, textureLoader* texture_loader, SDL_Rect* rect_ptr, int type);
    void update_sprite(double angle);


  private:
    SDL_Rect clips[4];
    int sprite_index;
    int transistion_delay;
    int t;

    SDL_Texture* sprite_sheet;

    SDL_Renderer* obj_renderer;
    textureLoader* t_loader;

    SDL_Rect* dest_rect;




};

#endif
