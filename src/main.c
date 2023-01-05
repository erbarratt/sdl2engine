//definition below needed to stop SDL lib making "main" a macro.
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdbool.h>

#include <engine/config/config_pub.h>
#include <engine/render/render_pub.h>
#include <engine/input/input_pub.h>
#include <engine/timers/timers_pub.h>

int main(int argc, char *argv[])
{

	//engine objects
		struct render_t * render = eNEW(render_t);
		eCONSTRUCT(render_t, render);

		struct input_t * input = eNEW(input_t);
		eCONSTRUCT(input_t, input);

		struct config_t * config = eNEW(config_t);
		eCONSTRUCT(config_t, config);

		struct timers_t * time = eNEW(timers_t);
		eCONSTRUCT(timers_t, time);

	//start timers @ x fps
		time->init(time, 60);

	//load config
		config->parseConfig(config, input);

	//create window
		render->init(render, 1920, 1080, 640, 360, 3);

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
				(vec2){(float)(render->renderWidth*0.5), (float)(render->renderHeight*0.5) },
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
