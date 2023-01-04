//definition below needed to stop SDL lib making "main" a macro.
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "lib/engine/config/sdl2engine_config_pub.h"
#include "lib/engine/render/sdl2engine_render_pub.h"
#include "lib/engine/input/sdl2engine_input_pub.h"
#include "lib/engine/time/sdl2engine_time_pub.h"

int main(int argc, char *argv[])
{

	//engine objects
		struct sdl2engine_render_t * render = eNEW(sdl2engine_render_t);
		eCONSTRUCT(sdl2engine_render_t, render);

		struct sdl2engine_input_t * input = eNEW(sdl2engine_input_t);
		eCONSTRUCT(sdl2engine_input_t, input);

		struct sdl2engine_config_t * config = eNEW(sdl2engine_config_t);
		eCONSTRUCT(sdl2engine_config_t, config);

		struct sdl2engine_time_t * time = eNEW(sdl2engine_time_t);
		eCONSTRUCT(sdl2engine_time_t, time);

	//start timers @ x fps
		time->init(time, 60);

	//load config
		config->parseConfig(config, input);

	//create window
		render->init(render, 800, 600);

	//main loop
		bool shouldQuit = false;
		SDL_Event event;

		while(!shouldQuit){

			eCALL(time, update);

			while(SDL_PollEvent(&event)){
				switch(event.type){
					case SDL_QUIT:
						shouldQuit = true;
						break;
				}
			}

			eCALL(input, update);

			eCALL(render, begin);

			render->quad(
				render,
				(vec2){(float)(render->width*0.5), (float)(render->height*0.5), },
				(vec2){50, 50},
				(vec4){0,1,0,1}
			);

			eCALL(render, end);

			eCALL(time, updateLate);

		}

	eDESTROY(render);
	eDESTROY(input);
	eDESTROY(config);
	eDESTROY(time);

	return 0;

}
