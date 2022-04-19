#include "fontManager.h"
#include <iostream>


void fontManager::init(SDL_Renderer* ren, const char* ttf, int height){
  if(TTF_Init() < 0){
      std::cout << "ERROR: " << TTF_GetError() << std::endl;
  }

  obj_renderer = ren;
  font = TTF_OpenFont(ttf, height);


}

void fontManager::display_text(const char* text, int x_pos, int y_pos){

  SDL_Color color = {255, 255, 255, 255};
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
  SDL_Texture *text_ure = SDL_CreateTextureFromSurface(obj_renderer, textSurface);

  SDL_FreeSurface(textSurface);
  textSurface = nullptr;

  SDL_Rect text_rect;
  text_rect.x = x_pos;
  text_rect.y = y_pos;

  SDL_QueryTexture(text_ure, NULL, NULL, &text_rect.w, &text_rect.h);
  SDL_RenderCopy(obj_renderer, text_ure, NULL, &text_rect);
}
