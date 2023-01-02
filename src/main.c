
//definition below needed to stop SDL lib making "main" a macro.
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "lib/engine/global/sdl2engine_global_pub.h"

int main(int argc, char *argv[])
{

	//instantiate global object and create window
	struct sdl2engine_global_t * global = eNEW(sdl2engine_global_t);
	eCONSTRUCT(sdl2engine_global_t, global);
	global->createWindow(global, 800,600);

	bool shouldQuit = false;

	while(!shouldQuit){

		SDL_Event event;

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					shouldQuit = true;
					break;
			}
		}

		global->render->begin();

		global->render->quad(
			global->render,
			(vec2){(float)(global->render->width*0.5), (float)(global->render->height*0.5), },
			(vec2){50, 50},
			(vec4){0,1,0,1}
		);

		global->render->end(global->render);

	}

	return 0;
}
