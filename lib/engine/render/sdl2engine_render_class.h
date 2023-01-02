#ifndef SDL2ENGINE_SDL2ENGINE_RENDER_CLASS_H
#define SDL2ENGINE_SDL2ENGINE_RENDER_CLASS_H

#include "../../eOOPc.h"
#include <SDL2/SDL.h>
#include "../linmath.h"

/**
* Render class PRIVATE vmt structure
*/
	struct sdl2engine_render_t_vmt {
		SDL_Window * (*initWindow)(void * eOBJ);
	};

//function declarations for private methods via vmt
	void sdl2engine_render_t_vmt_instantiate(void * eOBJ);
	SDL_Window * sdl2engine_render_t_initWindow(void * eOBJ);

/**
* Render class PRIVATE structure
*/
	typedef struct {

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

	} sdl2engine_render_t;

//function declarations for public methods
	void sdl2engine_render_t_init(void * eOBJ, int widthHere, int heightHere);
	void sdl2engine_render_t_begin(void * eOBJ);
	void sdl2engine_render_t_end(void * eOBJ);
	void sdl2engine_render_t_quad(void * eOBJ, vec2 pos, vec2 size, vec4 color);

#endif //SDL2ENGINE_SDL2ENGINE_RENDER_CLASS_H
