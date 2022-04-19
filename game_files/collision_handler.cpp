#include "collision_handler.h"





void collision_handler::collision_handler_init(particle_generator* pg){
  p_gen = pg;
  dead = false;

}

void collision_handler::handle_collision(gameObject * obj_1, std::string type_1, gameObject * obj_2, std::string type_2){

  player = NULL;
  boundry = NULL;
  enemy = NULL;

  if(type_1 == "player" || type_2 == "player"){
    if(type_1 == "boundry" || type_2 == "boundry"){
        if(type_1 == "player"){
          player_boundry_collision(obj_1, obj_2);
        }
        else{
          player_boundry_collision(obj_2, obj_1);
        }
    }
    else if(type_1 == "ENEMY" || type_2 == "ENEMY"){
        if(type_1 == "player"){
          player_ENEMY_collision(obj_1, obj_2);
        }
        else{
          player_ENEMY_collision(obj_2, obj_1);
        }
    }
  }
  else if(type_1 == "ENEMY" || type_2 == "ENEMY"){
    if(type_1 == "boundry" || type_2 == "boundry"){
        if(type_1 == "ENEMY"){
          enemy_boundry_collision(obj_1, obj_2);
        }
        else{
          enemy_boundry_collision(obj_2, obj_1);
        }
    }
  }


}


void collision_handler::player_boundry_collision(gameObject *p, gameObject * b){


  if(p->obj_get_x_vel() > 5 || p->obj_get_x_vel() < -5){
    //If velocity high enough start particle effect.
    int x_pos = p->obj_get_x();
    int y_pos = p->obj_get_y() + p->obj_get_height();
    if(p->obj_get_x_vel() > 0){
      p_gen->generate_particle(x_pos, y_pos, 8, 8, p->obj_get_x_vel(), p->obj_get_y_vel(), 4, 1, p->obj_get_x_vel());
    }
    else{
      p_gen->generate_particle(x_pos, y_pos, 8, 8, p->obj_get_x_vel(), p->obj_get_y_vel(), 4, 1, -1 * p->obj_get_x_vel());
    }



  }
}

void collision_handler::player_ENEMY_collision(gameObject *p, gameObject * e){
  dead = true;
}

bool collision_handler::is_dead(){
  return dead;
}

void collision_handler::enemy_boundry_collision(gameObject *e, gameObject * b){


  if(e->obj_get_x_vel() > 5 || e->obj_get_x_vel() < -5){
    //If velocity high enough start particle effect.
    int x_pos = e->obj_get_x();
    int y_pos = e->obj_get_y() + e->obj_get_height();
    if(e->obj_get_x_vel() > 0){
      p_gen->generate_particle(x_pos, y_pos, 8, 8, e->obj_get_x_vel(), e->obj_get_y_vel(), 4, 1, e->obj_get_x_vel());
    }
    else{
      p_gen->generate_particle(x_pos, y_pos, 8, 8, e->obj_get_x_vel(), e->obj_get_y_vel(), 4, 1, -1 * e->obj_get_x_vel());
    }



  }
}
