#ifndef SDL2ENGINE_SDL2ENGINE_CONFIG_PUB_H
#define SDL2ENGINE_SDL2ENGINE_CONFIG_PUB_H

/**
* Input class PUBLIC structure
*/
	struct sdl2engine_config_t{
		/**
		* \see sdl2engine_config_t_parseConfig
		*/
			void (*parseConfig)(void * eOBJ, void * inputObj);
	};

/**
* \see sdl2engine_config_t_instantiate
*/
	void sdl2engine_config_t_instantiate(void * eOBJ);

#endif //SDL2ENGINE_SDL2ENGINE_CONFIG_PUB_H
