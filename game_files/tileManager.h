#ifndef tile_Mngr_h
#define tile_Mngr_h

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "textureLoader.h"
#include <iostream>


class tileManager{

  public:
    void init(SDL_Renderer* ren, textureLoader* texture_loader, const char* graphic, int x_sheet, int y_sheet, int x_len, int y_len, int screen_x, int screen_y);
    void init_map(int map[5], int dup, int x, int y, int x_start, int y_start, int tile_size);
    void update_tiles(int x);
    void scrolling(int input);


  private:

    int tilemap[5];

    int scr_x;
    int scr_y;

    int x_map;
    int y_map;

    int dest_count;

    int offset;

    SDL_Rect src_clips[14*6];
    SDL_Rect dest_clips[(int)1280/90 + 1];

    int duplicating;

    SDL_Texture* tile_sheet;

    int t_length;
    int mt_length;



    SDL_Renderer* obj_renderer;
    textureLoader* t_loader;

    int scroll;


};

#endif
