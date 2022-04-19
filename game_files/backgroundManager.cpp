#include "backgroundManager.h"


void backgroundManager::init(SDL_Renderer* ren, textureLoader* texture_loader){
  obj_renderer = ren;
  t_loader = texture_loader;


	layer1 = t_loader->load_image("layer1.png");

  layer3 = t_loader->load_image("layer1.png");

	layer2 = t_loader->load_image("layer2.png");


  // set up dest rect for background
  dest_rect.x = 0;
  dest_rect.y = 0;
  dest_rect.w = 1280;
  dest_rect.h = 320;

  // source rect for background layer 1
  src_rect1.x = 0;
  src_rect1.y = 0;
  src_rect1.h = 320;
  src_rect1.w = 1280;

  // source rect for background layer 2
  src_rect2.x = 0;
  src_rect2.y = 0;
  src_rect2.h = 320;
  src_rect2.w = 1280;

  // source rect for background layer 3
  src_rect3.x = 350;
  src_rect3.y = 5;
  src_rect3.h = 320;
  src_rect3.w = 1280;

  //Save screen length
  length = 1920;

  // set layer scroll speed modifier
  layer1_scale = 3;
  layer2_scale = 2;
  layer3_scale = 4;

}

void backgroundManager::update_background(int x_vel){

  // Move each layer based on current player speed and layer speed modifier
  src_rect1.x = src_rect1.x + (x_vel / layer1_scale);

  src_rect2.x = src_rect2.x + (x_vel / layer2_scale);

  src_rect3.x = src_rect3.x + (x_vel / layer3_scale);


  // Keep layers inbound
  if( src_rect1.x > length){
    src_rect1.x = 0;
  }
  else if(src_rect1.x < 0){
    src_rect1.x = 1920;
  }

  if( src_rect2.x > length){
    src_rect2.x = 0;
  }
  else if(src_rect2.x < 0){
    src_rect2.x = 1920;
  }

  if( src_rect3.x > length){
    src_rect3.x = 0;
  }
  else if(src_rect3.x < 0){
    src_rect3.x = 1920;
  }

  //Render layers
  SDL_RenderCopy(obj_renderer, layer1, &src_rect1, &dest_rect);
  SDL_RenderCopy(obj_renderer, layer3, &src_rect3, &dest_rect);
  SDL_RenderCopy(obj_renderer, layer2, &src_rect2, &dest_rect);




}
