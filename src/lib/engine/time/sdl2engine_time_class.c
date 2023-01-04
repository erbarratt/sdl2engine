#include "sdl2engine_time_pub.h"
#include "sdl2engine_time_class.h"

#include "../../eOOPc.h"

#include <SDL2/SDL.h>

	void sdl2engine_time_t_init(void * eOBJ, uint8_t frameRateHere)
	{
		eSELF(sdl2engine_time_t);
	
		self->frameRate = frameRateHere;
		self->frame_delay = 1000 / frameRateHere;
	}

	void sdl2engine_time_t_update(void * eOBJ)
	{
		eSELF(sdl2engine_time_t);

		self->now = (uint32_t)SDL_GetTicks();
		self->delta = (self->now - self->last) / 1000;
		self->last = self->now;
		++self->frameCount;

		if (self->now - self->frameLast >= 1000) {
			self->frameRate = self->frameCount;
			self->frameCount = 0;
			self->frameLast = self->now;
		}
	}

	void sdl2engine_time_t_updateLate(void * eOBJ)
	{
		eSELF(sdl2engine_time_t);
		self->frame_time = (uint32_t)SDL_GetTicks() - self->now;

		if (self->frame_delay > self->frame_time) {
			SDL_Delay(self->frame_delay - self->frame_time);
		}
	}

/**
* Instantiate Time Object
* @param void* eOBJ self
* @return void
*/
	void sdl2engine_time_t_instantiate(void * eOBJ)
	{
		eSELF(sdl2engine_time_t);

		self->init = &sdl2engine_time_t_init;
		self->update = &sdl2engine_time_t_update;
		self->updateLate = &sdl2engine_time_t_updateLate;

	}
