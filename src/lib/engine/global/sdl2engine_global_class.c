#include "sdl2engine_global_pub.h"
#include "sdl2engine_global_class.h"

/**
* Instantiate global Object
* @param void* eOBJ self
* @return void
*/
	void sdl2engine_global_t_instantiate(void * eOBJ)
	{
		eSELF(sdl2engine_global_t);

		//define props
			self->render = eNEW(sdl2engine_render_t);
			eCONSTRUCT(sdl2engine_render_t, self->render);

		//define props
			self->render = eNEW(sdl2engine_render_t);
			eCONSTRUCT(sdl2engine_render_t, self->render);

	}

