#include "textureLoader.h"

void textureLoader::init(SDL_Renderer* ren){
  obj_renderer = ren;

  //Initialize image loading
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
  		std::cout << "Fail to load stuff for IMG" << std::endl;
  }

  imageSurface = NULL;

}


SDL_Texture* textureLoader::load_image(const char* graphic){

  imageSurface = IMG_Load(graphic);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(obj_renderer, imageSurface);

	SDL_FreeSurface(imageSurface);

  return texture;

}
