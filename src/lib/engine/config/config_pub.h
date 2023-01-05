#ifndef CONFIG_PUB_H
#define CONFIG_PUB_H

/**
* Input class PUBLIC structure
*/
	struct config_t{
		/**
		* \see config_t_parseConfig
		*/
			void (*parseConfig)(void * eOBJ, void * inputObj);
	};

/**
* \see config_t_instantiate
*/
	void config_t_instantiate(void * eOBJ);

#endif //CONFIG_PUB_H
