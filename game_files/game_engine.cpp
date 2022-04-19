#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "game_engine.h"



void game_engine::init(){

	pause = true;
	game_over = false;

  // Pointers to our window and surface
	SDL_Window* window = NULL;

	// Initialize SDL. SDL_Init will return -1 if it fails.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		// End the program
		return;
	}

	// Create our window
	window = SDL_CreateWindow("EVASIVE ACTION", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

  //Create the renderer
	my_renderer = SDL_CreateRenderer(window, -1, 0);


	// Update the window display
	SDL_UpdateWindowSurface(window);

	ground.x = 0;
	ground.y = 700;
	ground.w = 1280;
	ground.h = 20;

	font_m = new fontManager();
	font_m->init(my_renderer, "Courier Prime Code.ttf", 20);

	font_l = new fontManager();
	font_l->init(my_renderer, "Courier Prime Code.ttf", 50);

	t_loader = new textureLoader();
	t_loader->init(my_renderer);

	//Create Background Manager
	bg_mngr = new backgroundManager();
	bg_mngr->init(my_renderer, t_loader);


	// Create particle generator
	p_gen = new particle_generator();
	p_gen->particle_generator_init(my_renderer, t_loader);



	// Create collision collision_handler
	handler = new collision_handler();
  handler->collision_handler_init(p_gen);


	//Create collision detector
	col_d = new collision_detection();
	col_d->collision_init(handler);





	tl_mngr = new tileManager();
	tl_mngr->init(my_renderer, t_loader, "tiles.png", 14, 6, 32, 32, 1280, 720);
	int map[5];
	map[0] = 46;
	map[1] = 74;
	map[2] = 74;
	map[3] = 74;
	map[4] = 74;
	int *ptr = map;
	tl_mngr->init_map(ptr, 1, 5, 8, 0, 0, 90);

  //Create the GameObject and register with collision detection
  player = new gameObject();
  player->obj_init("./rockets.png", my_renderer, t_loader, 1, 100, 475, tl_mngr, 50, 50);
	col_d->reg_obj(player, "player");

	gameObject* g = new gameObject();
  g->obj_init("", my_renderer, t_loader, 0, 0, 660, tl_mngr, 1280, 60);
	col_d->reg_obj(g, "boundry");

	e_gen = new enemy_generator();
	e_gen->init(my_renderer, "rockets.png", t_loader, player, col_d, 25, 25, 180, 150, 5, 3, true, 420, 6);

	interface = new ui();
	interface->init(my_renderer, font_m, t_loader, player, "Fuel", 100, 540, 20, 50, 200);



  is_running = true;
	return;
}

void game_engine::HandleEvents(){
  SDL_Event game_event;
  SDL_PollEvent(&game_event);

  if(game_event.type == SDL_QUIT){
    is_running = false;
  }

	if(handler->is_dead()){
		game_over = true;
	}

	switch(game_event.type){
		case SDL_KEYDOWN:
			switch(game_event.key.keysym.sym){
				case SDLK_LEFT:
					player->set_state("LEFT");
					break;
				case SDLK_RIGHT:
					player->set_state("RIGHT");
					break;
				case SDLK_UP:
					player->set_state("UP");
					break;
				case SDLK_DOWN:
					player->set_state("DOWN");
					break;
				case SDLK_SPACE:
					if(pause){
						pause = false;
					}
					else{
						pause = true;
					}
					if(game_over){
						is_running = false;
					}
					break;
			}
			break;
		case SDL_KEYUP:
			switch(game_event.key.keysym.sym){
				case SDLK_LEFT:
					player->set_state("STOP_LEFT");
					break;
				case SDLK_RIGHT:
					player->set_state("STOP_RIGHT");
					break;
				case SDLK_UP:
					player->set_state("STOP_UP");
					break;
				case SDLK_DOWN:
					player->set_state("STOP_DOWN");
				break;
		}
		break;
	}

}

void game_engine::updateMechanics(double time_del){
	if(!pause && !game_over){
		col_d->check_collision();
		p_gen->update_particles();
	  player->obj_update(time_del);
		e_gen->update_enemy();
	}
}

void game_engine::render(){

	SDL_SetRenderDrawColor(my_renderer, 0, 0, 0, 255);
	SDL_RenderClear(my_renderer);



	SDL_SetRenderDrawColor(my_renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(my_renderer, &ground);

	bg_mngr->update_background(player->obj_get_x_vel());
	tl_mngr->update_tiles(player->obj_get_x_vel());
	p_gen->render_particles();
	e_gen->render_enemy();
  player->obj_render();

	interface->update_score(e_gen->get_survived());
	interface->display_ui();

	if(pause && !game_over){
		const char * pause_msg = "PAUSED";
		font_l->display_text(pause_msg, 540, 340);
		const char * clear_msg = "PRESS \"SPACE\" TO UNPAUSE";
		font_m->display_text(clear_msg, 500, 400);
	}

	if(game_over){
		display_score();
		const char * clear_msg = "PRESS \"SPACE\" TO CLOSE";
		font_m->display_text(clear_msg, 510, 380);
	}

	SDL_RenderPresent(my_renderer);
}


bool game_engine::get_game_is_running(){
  return is_running;
}

void game_engine::quit(){

}


void game_engine::display_score(){
	std::string score = "Score: " + std::to_string(e_gen->get_survived());
	const char* final = score.c_str();
	font_l->display_text(final, 520, 340);

}
