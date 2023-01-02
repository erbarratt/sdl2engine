
//definition below needed to stop SDL lib making "main" a macro.
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "lib/engine/global/sdl2engine_global_pub.h"

int main(int argc, char *argv[])
{

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

	}

	return 0;
}
