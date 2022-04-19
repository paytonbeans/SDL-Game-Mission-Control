#include "particle_generator.h"


void particle_generator::particle_generator_init(SDL_Renderer * renderer, textureLoader * t_l){
  ren = renderer;
  t_loader = t_l;

  sparks = t_loader->load_image("spark.png");
  //Load particle_del

  header = new particle();
  tail = new particle();

  header->set_next(tail);
  tail->set_prev(header);

  spark_clip.x = 0;
  spark_clip.y = 0;
  spark_clip.w = 85;
  spark_clip.h = 82;

}


void particle_generator::generate_particle(int start_x, int start_y, int start_height, int start_width, int start_xvel, int start_yvel, int life_span, int t, int c){

  if(t == 1){
    srand(time(NULL));
    for(int i = 0; i < c; i++){
      particle * p = new particle();

      double speed_mod = (1 - ((rand() % 5 + 6) / 10));

      int y_vel = (rand() % 15) * -1;
      int x_rand = rand() % 10 - 5;

      //velocity is uxed to determine max particle count, if velocity is negative use the absolute value
      if(start_xvel > 0){
        p->particle_init(start_x + x_rand + 20, start_y - 40, start_height, start_width, -1 * start_xvel * speed_mod, y_vel * speed_mod, life_span * speed_mod, t);
      }
      else{
        p->particle_init(start_x + x_rand + 60, start_y - 40, start_height, start_width, -1 * start_xvel * speed_mod, y_vel * speed_mod, life_span * speed_mod, t);
      }

      particle_reg(p);
    }
  }

}

void particle_generator::update_particles(){
  particle * iterator;
  iterator = header->get_next();

  int x, y, w, h, xvel, yvel, life_span, t;
  int count = 0;
  while(iterator != tail){
    count++;

    x = iterator->get_dest()->x;
    y = iterator->get_dest()->y;
    xvel = iterator->particle_get_x_vel();
    yvel = iterator->particle_get_y_vel();
    life_span = iterator->get_lifetime();


    iterator->get_dest()->x = x + xvel;
    iterator->get_dest()->y = y + yvel;

    if(yvel < 0){
      iterator->particle_set_y_vel(yvel + 1);
    }

    if(life_span <= 0){
      particle * hold = iterator;
      iterator = iterator->get_next();
      hold->particle_del();
    }
    else{
      iterator->set_lifetime(life_span - 1);
      iterator = iterator->get_next();
    }
  }
}


void particle_generator::render_particles(){
  particle * iterator;
  iterator = header->get_next();
  int t;

  int count = 0;
  while(iterator != tail){
    t = iterator->get_type();
    //if(t == 1){
      count ++;
      SDL_RenderCopy(ren, sparks, &spark_clip, iterator->get_dest());
    //}
    iterator = iterator->get_next();
  }

}

void particle_generator::particle_del(particle * p){

  p->get_prev()->set_next(p->get_next());
  p->get_next()->set_prev(p->get_prev());

  delete p;
}

void particle_generator::particle_reg(particle * p){
  p->set_prev(tail->get_prev());
  p->set_next(tail);
  p->get_prev()->set_next(p);
  tail->set_prev(p);
  if(p->get_prev() == header){
  }

}
