#include "playerSpriteManager.h"
#include <iostream>



void playerSpriteManager::init(const char* graphic, SDL_Renderer* ren, textureLoader* texture_loader, SDL_Rect* rect_ptr, int type){
  obj_renderer = ren;
  t_loader = texture_loader;
  dest_rect = rect_ptr;
  t = type;

  sprite_sheet = t_loader->load_image(graphic);


  //Set up sprite sheet clips
  if(type == 1){
    // player
    for(int i = 0; i < 4; i++){
      clips[i].x = 215 + i * 55;
      clips[i].y = 3 * 44;
      clips[i].h = 44;
      clips[i].w = 54;
    }
  }
  else if(type == 2){
    // enemy
    for(int i = 0; i < 4; i++){
      clips[i].x = 215 + i * 55;
      clips[i].y = 5 * 44;
      clips[i].h = 44;
      clips[i].w = 54;
    }
  }




}


void playerSpriteManager::update_sprite(double angle){

  SDL_Rect src_rect;

  if(transistion_delay > 0){
    transistion_delay -= 1;
  }
  else{
    transistion_delay = 4;
    sprite_index += 1;
    sprite_index = sprite_index % 4;
  }

  src_rect = clips[sprite_index];

  // render copy the selected sprite using the clip from the sprite sheet
  SDL_RenderCopyEx(obj_renderer, sprite_sheet, &src_rect, dest_rect, angle, NULL, SDL_FLIP_NONE);

}
