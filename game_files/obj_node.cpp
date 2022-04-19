#include "obj_node.h"
#include <iostream>
#include <string>


void obj_node::node_init(gameObject* obj, std::string t){

  type = t;
  next = nullptr;
  prev = nullptr;

  data = obj;

}

void obj_node::node_del(){
  next->set_prev(prev);
  prev->set_next(next);
  delete this;
}

std::string obj_node::get_type(){
  return type;
}

gameObject* obj_node::get_data(){
  return data;
}

void obj_node::set_next(obj_node* point){
  next = point;
}
void obj_node::set_prev(obj_node* point){
  prev = point;
}

obj_node* obj_node::get_next(){
  return next;
}

obj_node* obj_node::get_prev(){
  return prev;
}
