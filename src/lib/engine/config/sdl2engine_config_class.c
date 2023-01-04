#include "sdl2engine_config_class.h"
#include "sdl2engine_config_pub.h"

#include "../../eOOPc.h"
#include "../input/sdl2engine_input_pub.h"

#include <SDL2/SDL.h>

	void sdl2engine_config_t_parseConfig(void * eOBJ, void * inputObj)
	{
		eSELF(sdl2engine_config_t);
		struct sdl2engine_input_t *input = (struct sdl2engine_input_t *)inputObj;

		input->keybinds[INPUT_KEY_LEFT] = SDL_GetScancodeFromName("A");
		input->keybinds[INPUT_KEY_RIGHT] = SDL_GetScancodeFromName("D");
		input->keybinds[INPUT_KEY_UP] = SDL_GetScancodeFromName("W");
		input->keybinds[INPUT_KEY_DOWN] = SDL_GetScancodeFromName("S");
		input->keybinds[INPUT_KEY_ESCAPE] = SDL_GetScancodeFromName("Escape");
	}

	void sdl2engine_config_t_instantiate(void * eOBJ)
	{
		eSELF(sdl2engine_config_t);
		self->parseConfig = &sdl2engine_config_t_parseConfig;
	}
