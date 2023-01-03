#include "sdl2engine_global_pub.h"
#include "sdl2engine_global_class.h"

/**
* Create an SDL window
* @param void* eOBJ self
* @param int widthHere
* @param int heightHere
* @return void
*/
	void sdl2engine_global_t_createWindow(void * eOBJ, int widthHere, int heightHere)
	{
		eSELF(sdl2engine_global_t);
		self->render->init(self->render, widthHere, heightHere);
	}

	void sdl2engine_global_t_instantiate(void * eOBJ)
	{
		eSELF(sdl2engine_global_t);

		//define props
			self->render = eNEW(sdl2engine_render_t);
			eCONSTRUCT(sdl2engine_render_t, self->render);

		//public methods
			self->createWindow = &sdl2engine_global_t_createWindow;

	}

