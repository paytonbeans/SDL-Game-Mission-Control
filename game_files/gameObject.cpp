#include "gameObject.h"
#include <iostream>
#include <string>


void gameObject::obj_init(const char* graphic, SDL_Renderer* ren, textureLoader* texture_loader, int type, int start_x, int start_y, tileManager* t_mngr, int swidth, int sheight){
  obj_renderer = ren;
  tl_mngr = t_mngr;
  t_loader = texture_loader;


  x_pos = start_x;
  y_pos = start_y;
  resource = 100;
  resource_max = 100;
  min_consumption = 10;
  consumption_rate = 2;
  regen_delay = 0;

  acc = vel = a_acc = a_vel = angle = rads = 0;

  width = swidth;
  height = sheight;

  SDL_Rect new_rect;

  obj_rect = new_rect;

	obj_rect.x = start_x;
	obj_rect.y = start_y;
	obj_rect.w = width;
	obj_rect.h = height;

  spr_mngr = new playerSpriteManager();
  spr_mngr->init(graphic, ren, t_loader, &obj_rect, type);

}


void gameObject::obj_update(double time_del){
  if(state == "ENEMY"){

    vel += acc;

    x_pos += vel * std::cos(rads);
    y_pos += vel * std::sin(rads);

    if(angle > 360){
      angle = angle - 360;
    }
    else if(angle < 0){
      angle = angle + 360;
    }

    if(a_acc > 3){
      a_acc = 3;
    }
    else if(a_acc < -3){
      a_acc = -3;
    }

    if(a_vel > 3){
      a_vel = 3;
    }
    else if(a_vel < -3){
      a_vel = -3;
    }

    if(vel > 10){
      vel = 10;
    }
    else if(vel < 0){
      vel = 0;
    }
    if(acc > 5){
      acc = 5;
    }
    else if(acc < -5){
      acc = -5;
    }

    if(y_pos < 0){
      y_pos = 0;
    }

    if(y_pos > 720 - height - 20){
      y_pos = 720 - height - 20;

      if(angle > 90){
        angle = 180;
      }
      else if(angle < 90){
        angle = 0;
      }
    }

    rads = (angle * M_PI) / 180;

    obj_rect.x = x_pos;
    obj_rect.y = y_pos;
    obj_rect.w = width;
    obj_rect.h = height;
    return;
  }

  x_pos += vel * std::cos(rads);
  y_pos += vel * std::sin(rads);


  if(state == "IDLE"){

  }
  else if(state == "RIGHT"){
    if(resource > 0){
      a_acc += 1;
      regen_delay = 20;
    }
  }
  else if(state == "LEFT"){
    if(resource > 0){
      a_acc += -1;
      regen_delay = 20;
    }
  }
  else if(state == "UP"){
    if(resource > 0){
      acc += 1;
      regen_delay = 20;
    }
  }
  else if(state == "DOWN"){
    if(resource > 0){
      acc -= 1;
      regen_delay = 20;
    }
  }
  else if(state == "STOP_RIGHT" || state == "STOP_LEFT"){
    a_acc = 0;
    a_vel = 0;
    if(regen_delay > 0){
      regen_delay -= 1;
    }
    else{
      resource = resource + consumption_rate;
      if(resource > resource_max){
        resource = resource_max;
      }
    }
  }
  else if(state == "STOP_UP" || state == "STOP_DOWN"){
    acc = 0;
    if(regen_delay > 0){
      regen_delay -= 1;
    }
    else{
      resource = resource + consumption_rate;
      if(resource > resource_max){
        resource = resource_max;
      }
    }
  }
  else if(state == "DEAD"){

  }

  a_vel += a_acc;
  angle = angle + a_vel;

  vel += acc;

  if(angle > 360){
    angle = angle - 360;
  }
  else if(angle < 0){
    angle = angle + 360;
  }

  if(a_acc > 3){
    a_acc = 3;
  }
  else if(a_acc < -3){
    a_acc = -3;
  }

  if(a_vel > 3){
    a_vel = 3;
  }
  else if(a_vel < -3){
    a_vel = -3;
  }

  if(vel > 10){
    vel = 10;
  }
  else if(vel < 0){
    vel = 0;
  }
  if(acc > 5){
    acc = 5;
  }
  else if(acc < -5){
    acc = -5;
  }

  if(x_pos < 0 ){
    x_pos = 0;
    tl_mngr->scrolling(1);
  }
  else if(x_pos + width > 1280){
    x_pos = 1280 - width;
    tl_mngr->scrolling(1);
  }
  else{
    tl_mngr->scrolling(0);
  }

  if(y_pos < 0){
    y_pos = 0;
  }

  if(y_pos > 720 - height - 20){
    y_pos = 720 - height - 20;

    if(angle > 90){
      angle = 180;
    }
    else if(angle < 90){
      angle = 0;
    }
  }

  rads = (angle * M_PI) / 180;

  if(acc > 0){
    resource = resource - consumption_rate;
  }
  if(resource < 0){
    resource = 0;
  }



  obj_rect.x = x_pos;
  obj_rect.y = y_pos;
  obj_rect.w = width;
  obj_rect.h = height;

}

void gameObject::set_state(std::string new_state){
  state = new_state;
  if(state == "RIGHT" || state == "LEFT" || state == "UP" || state == "DOWN"){
    resource -= min_consumption;
  }
  else{
    regen_delay = 10;
  }
}

void gameObject::obj_render(){
  spr_mngr->update_sprite(angle);
}

int gameObject::obj_get_vel(){
  return vel;
}

void gameObject::obj_set_vel(int new_vel){
  vel = new_vel;
}

double gameObject::obj_get_angle(){
  return angle;
}

void gameObject::obj_set_angle(double a){
  angle = a;
}

int gameObject::obj_get_x(){
  return x_pos;
}

int gameObject::obj_get_y(){
  return y_pos;
}

int gameObject::obj_get_x_vel(){
  return vel * cos(rads);
}

int gameObject::obj_get_y_vel(){
  return vel * sin(rads);
}

int gameObject::obj_get_width(){
  return width;
}

int gameObject::obj_get_height(){
  return height;
}

int gameObject::get_resource(){
  return resource;
}

int gameObject::obj_get_lifespan(){
  return lifespan;
}

void gameObject::obj_set_lifespan(int time){
  lifespan = time;
}
