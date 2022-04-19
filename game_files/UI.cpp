#include "UI.h"
#include <iostream>

void ui::init(SDL_Renderer* ren, fontManager* font_manager, textureLoader* t_loader, gameObject* obj, const char* label, int max, int x_pos, int y_pos, int height, int width){
  obj_renderer = ren;
  font_m = font_manager;
  player = obj;
  fuel_label = label;
  fuel_max = max;
  fuel = fuel_max;

  SDL_Rect new_rect;
  box = new_rect;
  box.x = x_pos;
  box.y = y_pos;
  box.h = height;
  box.w = width;

  SDL_Rect bar_rect;
  bar = bar_rect;
  bar.x = x_pos + 5;
  bar.y = y_pos + height / 2 + 2;
  bar.h = height / 2 - 4;
  bar.w = width - 10;

  SDL_Rect level_rect;
  level = level_rect;
  level.x = x_pos + 5;
  level.y = y_pos + height / 2 + 2;
  level.h = height / 2 - 4;
  level.w = width - 10;

  bar_width = width - 10;


}

void ui::update_score(int fresh){
  score = fresh;
}


void ui::display_ui(){

  SDL_SetRenderDrawColor(obj_renderer, 192, 192, 192, 100);
  SDL_RenderFillRect(obj_renderer, &box);
  SDL_SetRenderDrawColor(obj_renderer, 255, 255, 255, 200);
  SDL_RenderFillRect(obj_renderer, &bar);
  double res = player->get_resource();
  double f = fuel_max;
  double value =  res / f;
  int final = value * bar_width;
  if(final < 0){
    final = 0;
  }
  level.w = final;
  SDL_SetRenderDrawColor(obj_renderer, 0, 255, 127, 200);
  SDL_RenderFillRect(obj_renderer, &level);

  font_m->display_text(fuel_label, box.x + 5, box.y + 2);
  std::string points = "Score: " + std::to_string(score);
	const char* msg = points.c_str();
  font_m->display_text(msg, box.x + 100, box.y + 2);

}
