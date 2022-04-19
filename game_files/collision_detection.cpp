#include "collision_detection.h"


void collision_detection::collision_init(collision_handler * h){

  handler = h;
  tail = new obj_node();
  header = new obj_node();

  header->set_next(tail);
  header->set_prev(nullptr);

  tail->set_prev(header);
  tail->set_next(nullptr);
}


void collision_detection::reg_obj(gameObject * obj, std::string type){
  obj_node * n_node = new obj_node();
  n_node->node_init(obj, type);
  //Set up new node pointers
  n_node->set_prev(tail->get_prev());
  n_node->set_next(tail);
  //Tail->prev now points to the new node at the end of the list
  tail->set_prev(n_node);
  // prev last node->next now points to new node instead of tail
  n_node->get_prev()->set_next(n_node);
}


void collision_detection::unreg_obj(gameObject * obj){
  obj_node * iterator = header->get_next();
  while(iterator->get_data() != obj && iterator != tail){
    iterator = iterator->get_next();
  }
  if(iterator != tail){
    iterator->node_del();
  }
}


void collision_detection::check_collision(){
  obj_node * iterator = header->get_next();
  obj_node * traveler = iterator->get_next();

  // Traverse the linked list of objects and check colliision with all following
  // objects in the list
  while(iterator != tail){
    traveler = iterator->get_next();
    // prep iterator object local variables
    int x_low = iterator->get_data()->obj_get_x();
    int x_high = x_low + iterator->get_data()->obj_get_width();
    int y_low = iterator->get_data()->obj_get_y();
    int y_high = y_low + iterator->get_data()->obj_get_height();

    while(traveler != tail){
      //Here we check for collision between iterator and traveler
      //Prep local variable for traveler object in question
      int xt_low = traveler->get_data()->obj_get_x();
      int xt_high = xt_low + traveler->get_data()->obj_get_width();
      int yt_low = traveler->get_data()->obj_get_y();
      int yt_high = yt_low + traveler->get_data()->obj_get_height();

      if( (x_low >= xt_low && x_low <= xt_high)
        || (x_high >= xt_low && x_high <= xt_high) ){
        // Possible collision
        //Now check y-cords for collision
        if( (y_low >= yt_low && y_low <= yt_high) || (y_high >= yt_low && y_high <= yt_high)){
          //Collision has occurred
          handler->handle_collision(iterator->get_data(), iterator->get_type(), traveler->get_data(), traveler->get_type());
        }
      }
      traveler = traveler->get_next();
    }
    // All collisions for iterator have been checked
    iterator = iterator->get_next();
  }

  //All possible collisions have been checked
  return;
}
