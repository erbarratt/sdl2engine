#ifndef GLOBAL_PUB_H
#define GLOBAL_PUB_H

#include "../render/render_pub.h"

/**
* Global class PUBLIC structure
*/
	struct global_t {

		struct render_t* render;
		struct input_t* input;

	};

/**
* Instantiate global Object
* @param void* eOBJ self
* @return void
*/
	void global_t_instantiate(void * eOBJ);

#endif //GLOBAL_PUB_H
