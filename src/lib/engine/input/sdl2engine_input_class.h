#ifndef SDL2ENGINE_SDL2ENGINE_INPUT_CLASS_H
#define SDL2ENGINE_SDL2ENGINE_INPUT_CLASS_H

#include <stdint.h>

/**
* Input class PRIVATE vmt structure
*/
	struct sdl2engine_input_t_vmt {

		/**
		* \see sdl2engine_input_t_updateKeyState
		*/
			void (*updateKeyState)(uint8_t currentState, keyState_t * keyStateHere);

	};

/**
* \struct Input class PRIVATE structure
*/
	typedef struct {
		struct sdl2engine_input_t_vmt * vmt;
	} sdl2engine_input_t;

#endif //SDL2ENGINE_SDL2ENGINE_INPUT_CLASS_H
