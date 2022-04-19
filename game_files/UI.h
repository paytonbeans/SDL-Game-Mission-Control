#ifndef UI_h
#define UI_h

#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "fontManager.h"
#include "gameObject.h"


class ui{

  public:
    void init(SDL_Renderer* ren, fontManager* font_manager, textureLoader* t_loader, gameObject* obj, const char* label, int max, int x_pos, int y_pos, int height, int width);
    void display_ui();
    void update_score(int fresh);


  private:

    SDL_Renderer * obj_renderer;
    fontManager * font_m;
    textureLoader * t_loader;
    gameObject * player;

    const char* fuel_label;
    int fuel;
    int fuel_max;
    int bar_width;

    int score;

    SDL_Rect box;
    SDL_Rect bar;
    SDL_Rect level;







};

#endif
