#include "tileManager.h"
#include <iostream>



void tileManager::init(SDL_Renderer* ren, textureLoader* texture_loader, const char* graphic, int x_sheet, int y_sheet, int x_len, int y_len, int screen_x, int screen_y){

  // Save the renderer and texture loader in member variables
  obj_renderer = ren;
  t_loader = texture_loader;




  //Initialize image loading
  tile_sheet = t_loader->load_image(graphic);


  //Tile size on screen
  t_length = x_len;
  scr_x = screen_x;
  scr_y = screen_y;

  //Initial offset is 0
  offset = 0;

  //Save number of destination dest clips
  dest_count = (int)1280/90 + 1;

  //Length of tiles on screen - hard-coded for now
  mt_length = 90;

  //Set up sprite sheet clips
  for(int y = 0; y < y_sheet; y++){
    for(int x = 0; x < x_sheet; x++){
      src_clips[x + (x_sheet * y)].x = x * t_length;
      src_clips[x + (x_sheet * y)].y = y * t_length;
      src_clips[x + (x_sheet * y)].h = t_length;
      src_clips[x + (x_sheet * y)].w = t_length;
    }
  }



  // Set up dest_clips
  for(int i = 0; i < dest_count; i ++){
    dest_clips[i].x = i * mt_length;
    dest_clips[i].y = scr_y - mt_length;
    dest_clips[i].h = mt_length;
    dest_clips[i].w = mt_length;
  }


}

void tileManager::init_map(int map[5], int dup, int x, int y, int x_start, int y_start, int tile_size){

  duplicating = dup;
  x_map = x;
  y_map = y;

  for(int i = 0; i < 5; i++){
    tilemap[i] = map[i];
  }
}


void tileManager::update_tiles(int x_vel){

  if(scroll){
    offset += x_vel;
    for(int i = 0; i < dest_count; i ++){
      dest_clips[i].x = dest_clips[i].x - x_vel;
    }
  }

  if(offset > dest_count * mt_length){
    offset = offset - (dest_count * mt_length);
  }

  //Check if tiles need to loop
  while(dest_clips[0].x + mt_length < 0){
    for(int i = 0; i < dest_count; i ++){
      dest_clips[i].x = dest_clips[i].x + mt_length;
    }
  }

  while(dest_clips[0].x > 0){
    for(int i = 0; i < dest_count; i ++){
      dest_clips[i].x = dest_clips[i].x - mt_length;
    }
  }

  //Populate dest_clips with src_clips
  int start_index = ((int)(offset / mt_length)) % 5;
  if(start_index < 0){
    start_index += 5;
  }

  // Render tiles to map
  for(int h = 0; h < dest_count; h++){
    SDL_RenderCopy(obj_renderer, tile_sheet, &src_clips[tilemap[(h + start_index) % 5]], &dest_clips[h]);
  }


}

// Keep track of screen scrolling
void tileManager::scrolling(int input){
  scroll = input;
}
