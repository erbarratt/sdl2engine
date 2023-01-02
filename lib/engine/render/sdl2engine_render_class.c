#include "sdl2engine_render_pub.h"
#include "sdl2engine_render_class.h"

//opengl loader
#include <glad/glad.h>
#include <SDL2/SDL.h>

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//VMT

/**
* Instantiate a Person class vmt
* @param void* eOBJ Self (Class vmt)
* @return void
*/
	void sdl2engine_render_t_vmt_instantiate(void * eOBJ)
	{
		//cast eOBJ back into class vmt type pointer
			eSELF(sdl2engine_render_t_vmt);

		//define private methods
			self->initWindow = &sdl2engine_render_t_initWindow;

	}

/**
* Initialise a window
* @param void* eOBJ Self (class)
* @return SDL_Window
*/
	SDL_Window * sdl2engine_render_t_initWindow(void * eOBJ)
	{
		//cast eOBJ back into class (NOT vmt!) type pointer
			eSELF(sdl2engine_render_t);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		if(SDL_Init(SDL_INIT_VIDEO) < 0){
			printf(cRED "Could not init SDL: %s\n" cRESET, SDL_GetError());
			exit(1);
		}

		SDL_Window * window = SDL_CreateWindow(
			"SDL2Engine",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			self->width,
			self->height,
			SDL_WINDOW_OPENGL
		);

		if(!window){
			printf(cRED "Could not init SDL window: %s\n" cRESET, SDL_GetError());
			exit(1);
		}

		SDL_GL_CreateContext(window);
		if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
			eDEBUG("Could not load GL: %s\n", SDL_GetError());
			exit(1);
		}

		puts("OpenGL Loaded");
		printf("Vendor: %s\n", glGetString(GL_VENDOR));
		printf("Renderer: %s\n", glGetString(GL_RENDERER));
		printf("Version: %s\n", glGetString(GL_VERSION));

		return window;

	}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//PUBLIC METHODS

/**
* Instantiate CPU object
* @param void* eOBJ self
* @return void
*/
	void sdl2engine_render_t_instantiate(void * eOBJ)
	{
		eSELF(sdl2engine_render_t);

		//public methods
			self->init = &sdl2engine_render_t_init;
			self->begin = &sdl2engine_render_t_begin;
			self->end = &sdl2engine_render_t_end;
			self->quad = &sdl2engine_render_t_quad;

		//private methods vmt
			self->vmt = eNEW(sdl2engine_render_t_vmt);
			eCONSTRUCT(sdl2engine_render_t_vmt, self->vmt);

	}

	void sdl2engine_render_t_init(void * eOBJ, int widthHere, int heightHere)
	{
		eSELF(sdl2engine_render_t);

		//define props
			self->width = widthHere;
			self->height = heightHere;
			self->window = self->vmt->initWindow(self);

	}

	void sdl2engine_render_t_begin(void * eOBJ)
	{

	}

	void sdl2engine_render_t_end(void * eOBJ)
	{

	}

	void sdl2engine_render_t_quad(void * eOBJ, vec2 pos, vec2 size, vec4 color)
	{

	}

