#ifndef SDL2ENGINE_SDL2ENGINE_RENDER_PUB_H
#define SDL2ENGINE_SDL2ENGINE_RENDER_PUB_H

#include "../../eOOPc.h"
#include <SDL2/SDL.h>
#include "../../linmath.h"


/**
* \struct Render class PUBLIC structure
*/
	struct sdl2engine_render_t {

		SDL_Window *window;
		int width;
		int height;

		/**
		* \see sdl2engine_render_t_init
		*/
			void (*init)(void * eOBJ, int widthHere, int heightHere);

		/**
		* \see sdl2engine_render_t_begin
		*/
			void (*begin)(void * eOBJ);

		/**
		* \see sdl2engine_render_t_end
		*/
			void (*end)(void * eOBJ);

		/**
		* \see sdl2engine_render_t_quad
		*/
			void (*quad)(void * eOBJ, vec2 pos, vec2 size, vec4 color);

		//private methods via virtual method table struct
			struct sdl2engine_render_t_vmt* vmt;

	};

	void sdl2engine_render_t_instantiate(void * eOBJ);

#endif //SDL2ENGINE_SDL2ENGINE_RENDER_PUB_H
