#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "game_engine.h"

using namespace std;

int main(){
  game_engine* ge = new game_engine();

  ge->init();

  int fps = 60;
	int frame_time = 1 + 1000 / fps;
	int frame_count = 0;
	double last_time = 0;
	double start_time;
  double this_duration = 0;
	int fps_counter = 0;

  while(ge->get_game_is_running()){
    start_time = SDL_GetTicks();

    ge->HandleEvents();
    ge->updateMechanics(this_duration);
    ge->render();



    frame_count++;
		if (start_time >= last_time + 1000) {
			last_time = start_time;
			fps_counter = frame_count;
			frame_count = 0;
		}

    cout << "FPS: " << fps_counter << endl;

    this_duration = SDL_GetTicks() - start_time;

    if(this_duration < frame_time){
      SDL_Delay(frame_time - this_duration);
    }



  }
  ge->quit();
  return 0;
}
