#ifndef SDL2ENGINE_SDL2ENGINE_GLOBAL_CLASS_H
#define SDL2ENGINE_SDL2ENGINE_GLOBAL_CLASS_H

#include "../render/sdl2engine_render_pub.h"

/**
* Render class PRIVATE structure
*/
	typedef struct {

		//public properties
			struct sdl2engine_render_t* render;

		//public methods
			void (*createWindow)(void * eOBJ, float widthHere, float heightHere);

	} sdl2engine_global_t;

//function declarations for public methods
	void sdl2engine_global_t_createWindow(void * eOBJ, float widthHere, float heightHere);

#endif //SDL2ENGINE_SDL2ENGINE_GLOBAL_CLASS_H
