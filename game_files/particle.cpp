#include "particle.h"


void particle::particle_init(int start_x, int start_y, int start_height, int start_width, int start_xvel, int start_yvel, int life_span, int t){


  dest = new SDL_Rect();

  dest->x = start_x;
  dest->y = start_y;
  dest->w = start_width;
  dest->h = start_height;

  x_vel = start_xvel;
  y_vel = start_yvel;

  lifetime = life_span;

  type = t;
  next = NULL;
  prev = NULL;
}



void particle::particle_del(){
  next->set_prev(prev);
  prev->set_next(next);
  delete this;
}

void particle::update_particle(int x, int y, int xvel, int yvel, int width, int height, int life_span){
  dest->x = x;
  dest->y = y;
  dest->w = width;
  dest->h = height;
  x_vel = xvel;
  y_vel = yvel;
  lifetime = life_span;
}

SDL_Rect * particle::get_dest(){
  return dest;
}

int particle::get_type(){
  return type;
}

int particle::get_lifetime(){
  return lifetime;
}

void particle::set_lifetime(int i){
  lifetime = i;
}

int particle::particle_get_x_vel(){
  return x_vel;
}

int particle::particle_get_y_vel(){
  return y_vel;
}

void particle::set_next(particle* point){
  next = point;
}
void particle::set_prev(particle* point){
  prev = point;
}

particle* particle::get_next(){
  return next;
}

particle* particle::get_prev(){
  return prev;
}

void particle::particle_set_y_vel(int yvel){
  y_vel = yvel;
}
