#ifndef SDL2ENGINE_SDL2ENGINE_RENDER_CLASS_H
#define SDL2ENGINE_SDL2ENGINE_RENDER_CLASS_H

#include "../../eOOPc.h"
#include <SDL2/SDL.h>
#include "../../linmath.h"

	struct stateInternal {
		uint32_t vao_quad;
		uint32_t vbo_quad;
		uint32_t ebo_quad;
		uint32_t shader_default;
		uint32_t texture_color;
		mat4x4 projection;
	};

/**
* Render class PRIVATE vmt structure
*/
	struct sdl2engine_render_t_vmt {

		struct stateInternal state;

		void (*initWindow)(void * eOBJ);
		void (*initQuad)(void * eOBJ, uint32_t *vao, uint32_t *vbo, uint32_t *ebo);
		void (*initColorTexture)(void * eOBJ, uint32_t *texture);
		void (*initShaders)(void * eOBJ);
		uint32_t (*shaderCreate)(const char * path_vert, const char * path_frag);

	};

/**
* \struct Render class PRIVATE structure
*/
	typedef struct {
		struct sdl2engine_render_t_vmt * vmt;
	} sdl2engine_render_t;

#endif //SDL2ENGINE_SDL2ENGINE_RENDER_CLASS_H
