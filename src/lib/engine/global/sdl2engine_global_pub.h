#ifndef SDL2ENGINE_SDL2ENGINE_GLOBAL_PUB_H
#define SDL2ENGINE_SDL2ENGINE_GLOBAL_PUB_H

#include "../render/sdl2engine_render_pub.h"

/**
* Global class PUBLIC structure
*/
	struct sdl2engine_global_t {

		struct sdl2engine_render_t* render;

		/**
		* \see sdl2engine_global_t_createWindow
		*/
			void (*createWindow)(void * eOBJ, int widthHere, int heightHere);

	};

/**
* Instantiate global Object
* @param void* eOBJ self
* @return void
*/
	void sdl2engine_global_t_instantiate(void * eOBJ);

#endif //SDL2ENGINE_SDL2ENGINE_GLOBAL_PUB_H
