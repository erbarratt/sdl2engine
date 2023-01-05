#ifndef RENDER_PUB_H
#define RENDER_PUB_H

#include "../../eOOPc.h"
#include <SDL2/SDL.h>
#include "../../linmath.h"


/**
* \struct Render class PUBLIC structure
*/
	struct render_t {

		SDL_Window *window;
		uint32_t windowWidth;
		uint32_t windowHeight;

		uint32_t renderWidth;
		uint32_t renderHeight;

		uint32_t scale;

		/**
		* \see render_t_init
		*/
			void (*init)(void * eOBJ, uint32_t windowWidthHere, uint32_t windowHeightHere, uint32_t renderWidthHere, uint32_t renderHeightHere, uint32_t scaleHere);

		/**
		* \see render_t_begin
		*/
			void (*begin)(void * eOBJ);

		/**
		* \see render_t_end
		*/
			void (*end)(void * eOBJ);

		/**
		* \see render_t_quad
		*/
			void (*quad)(void * eOBJ, vec2 pos, vec2 size, vec4 color);

		//private methods via virtual method table struct
			struct render_t_vmt* vmt;

	};

	void render_t_instantiate(void * eOBJ);

#endif //RENDER_PUB_H
