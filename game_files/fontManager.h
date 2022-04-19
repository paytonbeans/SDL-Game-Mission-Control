#ifndef font_manager_h
#define font_manager_h

#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


class fontManager{

  public:
    void init(SDL_Renderer* ren, const char* ttf, int height);
    void display_text(const char* text, int x_pos, int y_pos);


  private:

    SDL_Renderer *obj_renderer;

    TTF_Font *font;







};

#endif
