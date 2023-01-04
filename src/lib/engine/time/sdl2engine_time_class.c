#include "sdl2engine_time_pub.h"
#include "sdl2engine_time_class.h"

#include "../../eOOPc.h"

#include <SDL2/SDL.h>

	void sdl2engine_time_t_init(void * eOBJ, uint8_t frameRateHere)
	{
		eSELF(sdl2engine_time_t);
	
		self->frameRate = frameRateHere;
		self->frameDelay = 1000.f / (float)frameRateHere;
	}

	void sdl2engine_time_t_update(void * eOBJ)
	{
		eSELF(sdl2engine_time_t);

		self->now = (float)SDL_GetTicks();
		self->delta = (self->now - self->last) / 1000.f;
		self->last = self->now;
		++self->frameCount;

		if (self->now - self->frameLast >= 1000.f) {
			self->frameRate = self->frameCount;
			self->frameCount = 0;
			self->frameLast = self->now;
		}
	}

	void sdl2engine_time_t_updateLate(void * eOBJ)
	{
		eSELF(sdl2engine_time_t);
		self->frameTime = (float)SDL_GetTicks() - self->now;

		if (self->frameDelay > self->frameTime) {
			SDL_Delay(self->frameDelay - self->frameTime);
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
