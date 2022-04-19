#include "enemy_generator.h"
#include <iostream>


void enemy_generator::init(SDL_Renderer* ren, const char* graphic, textureLoader* t_loader, gameObject* player, collision_detection * col_d, int height, int width, double rate, int spawn_d, int speed, int turn_rate, bool wobble, int lifespan, int count){
  obj_renderer = ren;
  h = height;
  w = width;
  file = graphic;
  target = player;
  spawn_rate = rate;
  max_speed = speed;
  variance = wobble;
  lifetime = lifespan;
  angular_speed = turn_rate;
  spawn_delay = spawn_d;
  count = 0;
  max_count = 4;
  t_load = t_loader;
  t_mngr = nullptr;
  collision = col_d;
  survived = 0;


  tail_egen = new obj_node();
  header_egen = new obj_node();

  header_egen->set_next(tail_egen);
  header_egen->set_prev(nullptr);

  tail_egen->set_prev(header_egen);
  tail_egen->set_next(nullptr);
}

void enemy_generator::update_enemy(){

  if(count < max_count && spawn_delay <= 0){
    spawn_delay = spawn_rate;
    spawn_enemy();
  }
  else{
    spawn_delay--;
  }
  int target_x = target->obj_get_x();
  int target_y = target->obj_get_y();


  if(count > 0){
    obj_node * iter = header_egen->get_next();
    obj_node * hold = nullptr;

    // Traverse the linked list of objects and update enemy pathing

    while(iter != tail_egen){
      // prep iterator object local variables
      if(iter->get_data()->obj_get_lifespan() < 0){

        hold = iter->get_next();

        destroy_enemy(iter);
      }
      else{
        iter->get_data()->obj_set_lifespan(iter->get_data()->obj_get_lifespan() - 1);
        int enemy_x = iter->get_data()->obj_get_x();
        int enemy_y = iter->get_data()->obj_get_y();
        double enemy_angle = iter->get_data()->obj_get_angle();
        double target_angle;

        //Draw debug lines


        double variant;
        if(variance){
          srand(time(NULL));
          variant = ((rand() % 10) - 5) / 10 * angular_speed;
        }
        else{
          variant = 0;
        }

        if(enemy_x == target_x){
          if(enemy_y > target_y){
            if(enemy_angle > 270){
              iter->get_data()->obj_set_angle(iter->get_data()->obj_get_angle() - angular_speed + variant);
            }
            else{
              iter->get_data()->obj_set_angle(iter->get_data()->obj_get_angle() + angular_speed + variant);
            }
          }
          else{
            if(enemy_angle > 90){
              iter->get_data()->obj_set_angle(iter->get_data()->obj_get_angle() - angular_speed + variant);
            }
            else{
              iter->get_data()->obj_set_angle(iter->get_data()->obj_get_angle() + angular_speed + variant);
            }

          }
        }
        else{
          target_angle = atan((target_y - enemy_y) / (target_x - enemy_x));
          target_angle = (target_angle * 180) / M_PI;
          if(enemy_x > target_x){
            target_angle = target_angle + 90;
          }

          if(enemy_y > target_x){
            target_angle = target_angle + 90;
          }

          if(target_angle >= 360){
            target_angle = target_angle - 360;
          }

        }



        if(enemy_angle > target_angle){
          if((360 - enemy_angle + target_angle) < enemy_angle - target_angle){
            // Positive angular acceleration
            iter->get_data()->obj_set_angle(iter->get_data()->obj_get_angle() + angular_speed + variant);
          }
          else{
            // Negative angular acceleration
            iter->get_data()->obj_set_angle(iter->get_data()->obj_get_angle() - angular_speed + variant);
          }
        }
        else{
          if((360 - target_angle + enemy_angle) < target_angle - enemy_angle){
            // Negative angular acceleration check
            iter->get_data()->obj_set_angle(iter->get_data()->obj_get_angle() - angular_speed + variant);
          }
          else{
            // Positive angular acceleration
            iter->get_data()->obj_set_angle(iter->get_data()->obj_get_angle() + angular_speed + variant);
          }
        }
      }
      iter->get_data()->obj_set_vel(iter->get_data()->obj_get_vel() + abs((5 * (1 - iter->get_data()->obj_get_lifespan()/lifetime))));
      iter->get_data()->obj_update(1);
      // This enemy is now updated

      iter = iter->get_next();
    }
  }

}

void enemy_generator::spawn_enemy(){
  count++;
  gameObject * enemy = new gameObject();
  enemy->obj_init(file, obj_renderer, t_load, 2, 10, 10, t_mngr, w, h);
  enemy->obj_set_lifespan(lifetime);
  enemy->set_state("ENEMY");
  reg_enemy(enemy, "ENEMY");
  collision->reg_obj(enemy, "ENEMY");
  enemy->obj_set_vel(2);
}

void enemy_generator::reg_enemy(gameObject * obj, std::string type){
  /*
  if(header_egen == nullptr || header_egen->get_next() != tail_egen){
    std::cout << "Header Problem" << std::endl;
  }
  if(tail_egen == nullptr || tail_egen->get_prev() != header_egen){
    std::cout << "Header Problem" << std::endl;
  }
  */

  obj_node * new_node = new obj_node();
  new_node->node_init(obj, type);

  //Set up new node pointers
  new_node->set_prev(tail_egen->get_prev());
  new_node->set_next(tail_egen);

  //Tail->prev now points to the new node at the end of the list
  tail_egen->set_prev(new_node);

  // prev last node->next now points to new node instead of tail
  new_node->get_prev()->set_next(new_node);
  /*
  std::cout << "Tests" << std::endl;
  if(new_node->get_next() != tail_egen){
    std::cout << "fail 1" << std::endl;
  }
  if(tail_egen->get_prev() != new_node){
    std::cout << "fail 2" << std::endl;
  }
  if(new_node->get_prev()->get_next() != new_node){
    std::cout << "fail 3" << std::endl;
  }
  std::cout << "Passed" << std::endl;
  */
}

void enemy_generator::render_enemy(){
  obj_node * iterator;
  iterator = header_egen->get_next();

  while(iterator != tail_egen){
    iterator->get_data()->obj_render();
    iterator = iterator->get_next();
  }
}

void enemy_generator::destroy_enemy(obj_node * obj){
  collision->unreg_obj(obj->get_data());
  obj->node_del();
  count--;
  survived++;
}

int enemy_generator::get_survived(){
  return survived;
}
