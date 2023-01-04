#include "sdl2engine_input_pub.h"
#include "sdl2engine_input_class.h"

#include "../../eOOPc.h"

#include <SDL2/SDL.h>

//VMT

/**
* Update a given key's state
* @param uint8_t currentState
* @param keyState_t * keyStateHere
* @return void
*/
	static void sdl2engine_input_t_updateKeyState(uint8_t currentState, keyState_t * keyStateHere)
	{
		if(currentState){
			if(*keyStateHere > 0){
				*keyStateHere = KS_HELD;
			} else {
				*keyStateHere = KS_PRESSED;
			}
		} else {
			*keyStateHere = KS_UNPRESSED;
		}
	}

/**
* Instantiate input vmt Object
* @param void* eOBJ self
* @return void
*/
	void sdl2engine_input_t_vmt_instantiate(void * eOBJ)
	{
		//cast eOBJ back into class vmt type pointer
			eSELF(sdl2engine_input_t_vmt);

		//link functions
			self->updateKeyState = &sdl2engine_input_t_updateKeyState;
	}

/**
* Update input poll
* @param void* eOBJ self
* @return void
*/
	void sdl2engine_input_t_update(void * eOBJ)
	{
		eSELF(sdl2engine_input_t);

		const uint8_t * keyboardState = SDL_GetKeyboardState(NULL);

		self->vmt->updateKeyState(keyboardState[self->keybinds[INPUT_KEY_LEFT]], &self->left);
		self->vmt->updateKeyState(keyboardState[self->keybinds[INPUT_KEY_RIGHT]], &self->right);
		self->vmt->updateKeyState(keyboardState[self->keybinds[INPUT_KEY_UP]], &self->up);
		self->vmt->updateKeyState(keyboardState[self->keybinds[INPUT_KEY_DOWN]], &self->down);
		self->vmt->updateKeyState(keyboardState[self->keybinds[INPUT_KEY_ESCAPE]], &self->escape);

	}

/**
* Instantiate input Object
* @param void* eOBJ self
* @return void
*/
	void sdl2engine_input_t_instantiate(void * eOBJ)
	{
		eSELF(sdl2engine_input_t);

		//public methods
			self->update = &sdl2engine_input_t_update;

		//private methods vmt - also state
			self->vmt = eNEW(sdl2engine_input_t_vmt);
			eCONSTRUCT(sdl2engine_input_t_vmt, self->vmt);

		//default binds for now
			self->keybinds[INPUT_KEY_LEFT] = SDL_GetScancodeFromName("A");
			self->keybinds[INPUT_KEY_RIGHT] = SDL_GetScancodeFromName("D");
			self->keybinds[INPUT_KEY_UP] = SDL_GetScancodeFromName("W");
			self->keybinds[INPUT_KEY_DOWN] = SDL_GetScancodeFromName("S");
			self->keybinds[INPUT_KEY_ESCAPE] = SDL_GetScancodeFromName("Escape");

	}
