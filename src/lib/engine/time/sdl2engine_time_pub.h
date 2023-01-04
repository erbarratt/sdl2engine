#ifndef SDL2ENGINE_SDL2ENGINE_TIME_PUB_H
#define SDL2ENGINE_SDL2ENGINE_TIME_PUB_H

#include <stdint.h>

/**
* Time class PUBLIC structure
*/
	struct sdl2engine_time_t {

		uint32_t delta;
		uint32_t now;
		uint32_t last;

		uint32_t frameLast;
		uint32_t frame_delay;
		uint32_t frame_time;

		uint8_t frameRate;
		uint32_t frameCount;

		/**
		* \see sdl2engine_time_t_init
		*/
			void (*init)(void * eOBJ, uint8_t frameRateHere);

		/**
		* \see sdl2engine_time_t_update
		*/
			void (*update)(void * eOBJ);

		/**
		* \see sdl2engine_time_t_updateLate
		*/
			void (*updateLate)(void * eOBJ);

	};

/**
* \see sdl2engine_input_t_instantiate
*/
	void sdl2engine_time_t_instantiate(void * eOBJ);

#endif //SDL2ENGINE_SDL2ENGINE_TIME_PUB_H
