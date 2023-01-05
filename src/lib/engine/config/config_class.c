#include "config_class.h"
#include "config_pub.h"

#include "../../eOOPc.h"
#include "../input/input_pub.h"

#include <SDL2/SDL.h>

	void config_t_parseConfig(void * eOBJ, void * inputObj)
	{
		eSELF(config_t);
		struct input_t *input = (struct input_t *)inputObj;

		input->keybinds[INPUT_KEY_LEFT] = SDL_GetScancodeFromName("A");
		input->keybinds[INPUT_KEY_RIGHT] = SDL_GetScancodeFromName("D");
		input->keybinds[INPUT_KEY_UP] = SDL_GetScancodeFromName("W");
		input->keybinds[INPUT_KEY_DOWN] = SDL_GetScancodeFromName("S");
		input->keybinds[INPUT_KEY_ESCAPE] = SDL_GetScancodeFromName("Escape");
	}

	void config_t_instantiate(void * eOBJ)
	{
		eSELF(config_t);
		self->parseConfig = &config_t_parseConfig;
	}
