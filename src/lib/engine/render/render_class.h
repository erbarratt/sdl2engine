#ifndef RENDER_CLASS_H
#define RENDER_CLASS_H

#include "../../eOOPc.h"
#include <SDL2/SDL.h>
#include "../../linmath.h"

	struct stateInternal {
		uint32_t vaoQuad; //vertex array object
		uint32_t vboQuad; //vertex array buffer object
		uint32_t eboQuad; //element array buffer
		uint32_t shaderDefault;
		uint32_t textureColor;
		mat4x4 projection;
	};

/**
* Render class PRIVATE vmt structure
*/
	struct render_t_vmt {

		struct stateInternal state;

		/**
		* \see render_t_initWindow
		*/
			void (*initWindow)(void * eOBJ);

		/**
		* \see render_t_initQuad
		*/
			void (*initQuad)(void * eOBJ);

		/**
		* \see render_t_initColorTexture
		*/
			void (*initColorTexture)(void * eOBJ);

		/**
		* \see render_t_initShaders
		*/
			void (*initShaders)(void * eOBJ);

		/**
		* \see render_t_shaderCreate
		*/
			uint32_t (*shaderCreate)(const char * path_vert, const char * path_frag);

	};

/**
* \struct Render class PRIVATE structure
*/
	typedef struct {
		struct render_t_vmt * vmt;
	} render_t;

#endif //RENDER_CLASS_H
