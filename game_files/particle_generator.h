#ifndef particle_generator_h
#define particle_generator_h


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "textureLoader.h"
#include "particle.h"
#include <stdlib.h>
#include <time.h>


class particle_generator{

public:

  void particle_generator_init(SDL_Renderer * renderer, textureLoader * t_l);

  void generate_particle(int start_x, int start_y, int start_height, int start_width, int start_xvel, int start_yvel, int life_span, int t, int c);

  void update_particles();

  void render_particles();

  void particle_del(particle * p);
  void particle_reg(particle * p);

private:

  SDL_Renderer * ren;
  textureLoader * t_loader;
  particle * header;
  particle * tail;
  SDL_Texture * sparks;
  SDL_Rect spark_clip;


};

#endif
