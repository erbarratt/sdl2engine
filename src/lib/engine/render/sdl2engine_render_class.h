#ifndef SDL2ENGINE_SDL2ENGINE_RENDER_CLASS_H
#define SDL2ENGINE_SDL2ENGINE_RENDER_CLASS_H

#include "../../eOOPc.h"
#include <SDL2/SDL.h>
#include "../linmath.h"

	typedef struct stateInternal {
		uint32_t vao_quad;
		uint32_t vbo_quad;
		uint32_t ebo_quad;
		uint32_t shader_default;
		uint32_t texture_color;
		mat4x4 projection;
	} stateInternal;

/**
* Render class PRIVATE vmt structure
*/
	struct sdl2engine_render_t_vmt {
		SDL_Window * (*initWindow)(void * eOBJ);
		void (*initQuad)(void * eOBJ, uint32_t *vao, uint32_t *vbo, uint32_t *ebo);
		void (*initColorTexture)(void * eOBJ, uint32_t *texture);
		void (*initShaders)(void * eOBJ);
		uint32_t (*shaderCreate)(const char * path_vert, const char * path_frag);
		struct stateInternal state;
	};

//function declarations for private methods via vmt
	void sdl2engine_render_t_vmt_instantiate(void * eOBJ);
	SDL_Window * sdl2engine_render_t_initWindow(void * eOBJ);
	void sdl2engine_render_t_initQuad(void * eOBJ, uint32_t *vao, uint32_t *vbo, uint32_t *ebo);
	void sdl2engine_render_t_initColorTexture(void * eOBJ, uint32_t *texture);
	void sdl2engine_render_t_initShaders(void * eOBJ);
	uint32_t sdl2engine_render_t_shaderCreate(const char * path_vert, const char * path_frag);

/**
* Render class PRIVATE structure
*/
	typedef struct {

		//public properties
			SDL_Window *window;
			int width;
			int height;

		//public methods
			void (*init)(void * eOBJ, int widthHere, int heightHere);
			void (*begin)();
			void (*end)(void * eOBJ);
			void (*quad)(void * eOBJ, vec2 pos, vec2 size, vec4 color);

		//private methods via virtual method table struct
			struct sdl2engine_render_t_vmt * vmt;

	} sdl2engine_render_t;

//function declarations for public methods
	void sdl2engine_render_t_init(void * eOBJ, int widthHere, int heightHere);
	void sdl2engine_render_t_begin();
	void sdl2engine_render_t_end(void * eOBJ);
	void sdl2engine_render_t_quad(void * eOBJ, vec2 pos, vec2 size, vec4 color);

#endif //SDL2ENGINE_SDL2ENGINE_RENDER_CLASS_H
