#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

#include <stdint.h>

/**
* Input class PRIVATE vmt structure
*/
	struct input_t_vmt {

		/**
		* \see input_t_updateKeyState
		*/
			void (*updateKeyState)(uint8_t currentState, keyState_t * keyStateHere);

	};

/**
* \struct Input class PRIVATE structure
*/
	typedef struct {
		struct input_t_vmt * vmt;
	} input_t;

#endif //INPUT_CLASS_H
