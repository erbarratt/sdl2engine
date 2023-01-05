#ifndef TIME_PUB_H
#define TIME_PUB_H

#include <stdint.h>

/**
* Time class PUBLIC structure
*/
	struct timers_t {

		float delta;
		float now;
		float last;

		float frameLast;
		float frameDelay;
		float frameTime;

		uint8_t frameRate;
		uint32_t frameCount;

		/**
		* \see timers_t_init
		*/
			void (*init)(void * eOBJ, uint8_t frameRateHere);

		/**
		* \see timers_t_update
		*/
			void (*update)(void * eOBJ);

		/**
		* \see timers_t_updateLate
		*/
			void (*updateLate)(void * eOBJ);

	};

/**
* \see input_t_instantiate
*/
	void timers_t_instantiate(void * eOBJ);

#endif //TIME_PUB_H
