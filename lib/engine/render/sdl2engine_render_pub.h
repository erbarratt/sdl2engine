#ifndef SDL2ENGINE_SDL2ENGINE_RENDER_PUB_H
#define SDL2ENGINE_SDL2ENGINE_RENDER_PUB_H

#include "../../eOOPc.h"
#include <SDL2/SDL.h>
#include "../linmath.h"

/**
* Render class PUBLIC structure
*/
	struct sdl2engine_render_t {

		//public properties
			SDL_Window *window;
			int width;
			int height;

		//public methods
			void (*init)(void * eOBJ, int widthHere, int heightHere);
			void (*begin)(void * eOBJ);
			void (*end)(void * eOBJ);
			void (*quad)(void * eOBJ, vec2 pos, vec2 size, vec4 color);

		//private methods via virtual method table struct
			struct sdl2engine_render_t_vmt* vmt;

	};

	void sdl2engine_render_t_instantiate(void * eOBJ);

#endif //SDL2ENGINE_SDL2ENGINE_RENDER_PUB_H
