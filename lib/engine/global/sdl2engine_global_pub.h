#ifndef SDL2ENGINE_SDL2ENGINE_GLOBAL_PUB_H
#define SDL2ENGINE_SDL2ENGINE_GLOBAL_PUB_H

#include "../render/sdl2engine_render_pub.h"

/**
* Global class PUBLIC structure
*/
	struct sdl2engine_global_t {

		//public properties
			struct sdl2engine_render_t* render;

		//public methods
			void (*createWindow)(void * eOBJ, float widthHere, float heightHere);

	};

	void sdl2engine_global_t_instantiate(void * eOBJ);

#endif //SDL2ENGINE_SDL2ENGINE_GLOBAL_PUB_H
