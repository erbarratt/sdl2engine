#ifndef INPUT_PUB_H
#define INPUT_PUB_H

#include <stdint.h>

	typedef enum inputKey {
		INPUT_KEY_LEFT = 0,
		INPUT_KEY_RIGHT = 1,
		INPUT_KEY_UP = 2,
		INPUT_KEY_DOWN = 3,
		INPUT_KEY_ESCAPE = 4
	} inputKey_t;

	typedef enum keyState{
		KS_UNPRESSED,
		KS_PRESSED,
		KS_HELD
	} keyState_t;

/**
* Input class PUBLIC structure
*/
	struct input_t {

		uint8_t keybinds[5];
		keyState_t left;
		keyState_t right;
		keyState_t up;
		keyState_t down;
		keyState_t escape;

		/**
		* \see input_t_update
		*/
			void (*update)(void * eOBJ);

		//private methods via virtual method table struct
			struct input_t_vmt* vmt;

	};

/**
* \see input_t_instantiate
*/
	void input_t_instantiate(void * eOBJ);

#endif //INPUT_PUB_H
