#include "render_pub.h"
#include "render_class.h"

//opengl loader
#include <glad/include/glad/glad.h>
#include <SDL2/SDL.h>

#include "../../utils.h"
#include "../io/io.h"

#define SELF_TYPE render_t

//when in dev, executable will be in cmake subfolder
//therefor, to open a file in project root, we need to shift up one directory first
//set in utils
#ifdef SDL2DEBUG
	#define DIR_SHIFT "../"
#endif

#ifndef SDL2DEBUG
	#define DIR_SHIFT
#endif

//VMT

/**
* Initialise a window
* @param void* eOBJ Self (class)
* @return void
*/
	static void render_t_initWindow(void * eOBJ)
	{
		//cast eOBJ back into class (NOT vmt!) type pointer
			eSELF(SELF_TYPE);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0){
			ERROR_EXIT(cRED "Could not init SDL: %s\n" cRESET, SDL_GetError());
		}

		SDL_Window * window = SDL_CreateWindow(
			"SDL2Engine",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			self->windowWidth,
			self->windowHeight,
			SDL_WINDOW_OPENGL
		);

		if(window == NULL){
			ERROR_EXIT(cRED "Could not init SDL window: %s\n" cRESET, SDL_GetError());
		}

		SDL_GL_CreateContext(window);
		if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
			ERROR_EXIT("Could not load GL: %s\n", SDL_GetError());
		}

		//due to buffering, will output once program is closed
		puts("OpenGL Loaded");
		printf("Vendor: %s\n", glGetString(GL_VENDOR));
		printf("Renderer: %s\n", glGetString(GL_RENDERER));
		printf("Version: %s\n", glGetString(GL_VERSION));

		self->window = window;

	}

/**
* Initialise a quad and store for use in state member
* render_t_quad uses this default quad to manipulate and draw instead of creating a new quad every time
* @param void* eOBJ Self (class)
* @return SDL_Window
*/
	static void render_t_initQuad(void * eOBJ)
	{
		//cast eOBJ back into class (NOT vmt!) type pointer
			eSELF(SELF_TYPE);

		// x, y, z, u, v
		//quad of "size" 1, with origin bottom left

		//	float vertices[] = {
		//		-0.5f, 0.5f, 0, 1, 0,
		//		0.5f, 0.5f, 0,0,0,
		//		0.5f, -0.5f, 0, 0, 1,
		//		-0.5f, -0.5f, 0, 1, 1,
		//	};

			float vertices[] = {
				0, 1, 0, 0, 1,
				1, 1, 0,1,1,
				1, 0, 0, 0, 1,
				0, 0, 0, 0, 0,
			};

		//		_______
		//		0    /1
		//		|  /  |
		//		3/____2
		//
			uint32_t indices [] = {
				0, 1, 3,
				1, 2, 3
			};

		//store into state members
		//generate vertex array object names
			glGenVertexArrays(1, &self->vmt->state.vaoQuad);

		//generate buffer object names
			glGenBuffers(1, &self->vmt->state.vboQuad);
			glGenBuffers(1, &self->vmt->state.eboQuad);

		// bind a vertex array object into the DATA of the now named array object
			glBindVertexArray(self->vmt->state.vaoQuad);

		//bind a named buffer object - GL_ARRAY_BUFFER - Vertex attributes
		//i.e. get buffer ready for vertices
			glBindBuffer(GL_ARRAY_BUFFER, self->vmt->state.vboQuad);
		//put the vertices data into the buffer
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//now do the same with vertex indices
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->vmt->state.eboQuad);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//xyz
		//define an array of generic vertex attribute data, at index 0
			glVertexAttribPointer(
				0,							//index 0, i.e. first
				3, 							//number of components per attribute (i.e. first 3 in each array line of vertices above
				GL_FLOAT, 					//stored as floats
				GL_FALSE, 					//don't normalize
				5*sizeof(float), 			//byte offset between vertices (lines in array above), 5 as each line is 5 elements
				NULL						//start at beginning of line (x)
			);
		//Enable or disable a generic vertex attribute array, at index 0 - just created
			glEnableVertexAttribArray(0);

		//uv
			glVertexAttribPointer(
				1,								//index 1 (second)
				2, 								//number of components per attribute u,v
				GL_FLOAT, 						//as floats
				GL_FALSE, 						//don't normalize
				5*sizeof(float), 				//byte offset between vertices (lines in array above), 5 as each line is 5 elements
				(void*)(3 * sizeof(float ) )	//start at 4th element (u)
			);
		//Enable or disable a generic vertex attribute array, at index 1 - just created
			glEnableVertexAttribArray(1);

		glBindVertexArray(0);

	}

/**
* Initialise a color texture and store for use in state member
* @param void* eOBJ Self (class)
* @return SDL_Window
*/
	static void render_t_initColorTexture(void * eOBJ)
	{
		//cast eOBJ back into class (NOT vmt!) type pointer
			eSELF(SELF_TYPE);

		glGenTextures(1, &self->vmt->state.textureColor);
		glBindTexture(GL_TEXTURE_2D, self->vmt->state.textureColor);
		uint8_t color[] = {255,255,255,255};
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, color);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

/**
* Initialise default shaders and store for use in state member
* @param void* eOBJ Self (class)
* @return SDL_Window
*/
	static void render_t_initShaders(void * eOBJ)
	{
		//cast eOBJ back into class (NOT vmt!) type pointer
			eSELF(SELF_TYPE);

		self->vmt->state.shaderDefault = self->vmt->shaderCreate(DIR_SHIFT"shaders/default.vert", DIR_SHIFT"shaders/default.frag");

		//orthographic projection in case of 640 x 360 =
		//i.e. create projection matrix to use in the default shader programs

		//	M[0][0] = 2.f/(640-0) = 0.003125;
		//	M[0][1] = M[0][2] = M[0][3] = 0.f;
		//
		//	M[1][1] = 2.f/(360-0) = 0.00555555555;
		//	M[1][0] = M[1][2] = M[1][3] = 0.f;
		//
		//	M[2][2] = -2.f/(2- -2) = -0.5;
		//	M[2][0] = M[2][1] = M[2][3] = 0.f;
		//
		//	M[3][0] = -(640+0)/(640-0) = -1;
		//	M[3][1] = -(360+0)/(360-0) = -1;
		//	M[3][2] = -(2+ -2)/(2- -2) = -0;
		//	M[3][3] = 1.f;
		//
		//	[0.003125 0 0 0]
		//	[0 0.00555555555 0 0]
		//	[0 0 -0.5 0]
		//	[-1 -1 0 1]

		mat4x4_ortho(self->vmt->state.projection, 0, self->renderWidth, 0, self->renderHeight, -2, 2);

		//set which program we're using
			glUseProgram(self->vmt->state.shaderDefault);

		//put that projection matrix as the value in the uniform projection object in the shader
		glUniformMatrix4fv(
			glGetUniformLocation(self->vmt->state.shaderDefault, "projection"),
			1,
			GL_FALSE,
			&self->vmt->state.projection[0][0]
		);

	}

/**
* Create a shader object using file locations and return pointer to object
* @param const char * path_vert
* @param const char * path_frag
* @return uint32_t pointer address
*/
	static uint32_t render_t_shaderCreate(const char * path_vert, const char * path_frag)
	{
		int success;
		char log[512];

		File file_vertex = io_file_read(path_vert);
		if (!file_vertex.is_valid) {
			ERROR_EXIT("Error reading shader: %s\n", path_vert);
		}
	
		uint32_t shader_vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shader_vertex, 1, (const char *const *)&file_vertex, NULL);
		glCompileShader(shader_vertex);
		glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader_vertex, 512, NULL, log);
			ERROR_EXIT("Error compiling vertex shader. %s\n", log);
		}

		File file_fragment = io_file_read(path_frag);
		if (!file_fragment.is_valid) {
			ERROR_EXIT("Error reading shader: %s\n", path_frag);
		}

		uint32_t shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(shader_fragment, 1, (const char *const *)&file_fragment, NULL);
		glCompileShader(shader_fragment);
		glGetShaderiv(shader_fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader_fragment, 512, NULL, log);
			ERROR_EXIT("Error compiling fragment shader. %s\n", log);
		}

		uint32_t shader = glCreateProgram();
		glAttachShader(shader, shader_vertex);
		glAttachShader(shader, shader_fragment);
		glLinkProgram(shader);
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 512, NULL, log);
			ERROR_EXIT("Error linking shader. %s\n", log);
		}

		free(file_vertex.data);
		free(file_fragment.data);

		return shader;
	}

/**
* Instantiate a Person class vmt
* @param void* eOBJ Self (Class vmt)
* @return void
*/
	void render_t_vmt_instantiate(void * eOBJ)
	{
		//cast eOBJ back into class vmt type pointer
			eSELF(render_t_vmt);

		//define private methods
			self->initWindow = &render_t_initWindow;
			self->initQuad = &render_t_initQuad;
			self->initColorTexture = &render_t_initColorTexture;
			self->initShaders = &render_t_initShaders;
			self->shaderCreate = &render_t_shaderCreate;

	}

//PUBLIC METHODS

/**
* Initialise the window, and quad values in render internal state
* @id render_t_init
* @function init
* @param void* eOBJ self
* @param int widthHere window width
* @param int heightHere window height
* @return void
*/
	static void render_t_init(void * eOBJ, uint32_t windowWidthHere, uint32_t windowHeightHere, uint32_t renderWidthHere, uint32_t renderHeightHere, uint32_t scaleHere)
	{
		eSELF(SELF_TYPE);

		//define props
			self->windowWidth = windowWidthHere;
			self->windowHeight = windowHeightHere;
			self->renderWidth = renderWidthHere;
			self->renderHeight = renderHeightHere;
			self->scale = scaleHere;

		//actually create window
			self->vmt->initWindow(self);

		//initiase state members
			self->vmt->initQuad(self);
			self->vmt->initShaders(self);
			self->vmt->initColorTexture(self);

			// enable or disable server-side GL capabilities
			// blend the computed fragment color values with the values in the color buffers.
			glEnable(GL_BLEND);

			//specify pixel arithmetic
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}

/**
* Begin Rendering a frame
* @return void
*/
	static void render_t_begin(void * eOBJ)
	{
		//specify clear values for the color buffers
		glClearColor(0, 0, 0, 1);

		//clear buffers to preset values
		//GL_COLOR_BUFFER_BIT = the buffers currently enabled for color writing.
		glClear(GL_COLOR_BUFFER_BIT);
	}

/**
* End Rendering a frame
* @param void* eOBJ self
* @return void
*/
	static void render_t_end(void * eOBJ)
	{
		eSELF(SELF_TYPE);
		//Update a window with OpenGL rendering, i.e. send drawn frame to window
		SDL_GL_SwapWindow(self->window);
	}

/**
* Render a quad
* @param void* eOBJ self
* @param vec2 pos
* @param vec2 size
* @param vec4 color
* @return void
*/
	static void render_t_quad(void * eOBJ, vec2 pos, vec2 size, vec4 color)
	{
		eSELF(SELF_TYPE);

		//Installs a program object as part of current rendering state
			glUseProgram(self->vmt->state.shaderDefault);

		//matrix
			mat4x4 model;

		//translate does mat4x4_identity()
		//
		//	[1 0 0 0]
		//	[0 1 0 0]
		//	[0 0 1 0]
		//	[0 0 0 1]
		//
		//then applies:
		//
		//	[1 0 0 0]
		//	[0 1 0 0]
		//	[0 0 1 0]
		//	[x y z 1]

		mat4x4_translate(model, pos[0], pos[1], 0);

		//scale each element by a factor in x, y, z
		//[3] element of matrix is simply duplicated
		//second arg = same matrix means scaling by itself
		//eg scale to x = 50, y = 50, z = 1
		//
		//	[50 0 0 0]
		//	[0 50 0 0]
		//	[0 0 1 0]
		//	[x y z 1]

		mat4x4_scale_aniso(model, model, size[0], size[1], 1);

		//put the values into the shader

			//Specify the value of a uniform variable for the current program object
				glUniformMatrix4fv(
					glGetUniformLocation(self->vmt->state.shaderDefault, "model"), 	//Specifies the location of the uniform variable to be modified - must be an active uniform variable name in program that is not a structure, an array of structures, or a subcomponent of a vector or a matrix.
					1,																//number of matrices to be modified
					GL_FALSE,														//transpose = no
					&model[0][0]													//pointer to start of the matrix
				);
			//Specify the value of a uniform variable for the current program object
				glUniform4fv(
					glGetUniformLocation(self->vmt->state.shaderDefault, "color"), 	//get location of color uniform variable in shader stored in shaderDefault
					1, 																//number of elements to modify
					color															//color values
				);

		//bind current data to quad
			glBindVertexArray(self->vmt->state.vaoQuad);

		//bind textureColor data into texture 2d
			glBindTexture(GL_TEXTURE_2D, self->vmt->state.textureColor);

		//actually render the primitive
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		glBindVertexArray(0);

	}

/**
* Instantiate Render object
* @param void* eOBJ self
* @return void
*/
	void render_t_instantiate(void * eOBJ)
	{
		eSELF(SELF_TYPE);

		//public methods
			self->init = &render_t_init;
			self->begin = &render_t_begin;
			self->end = &render_t_end;
			self->quad = &render_t_quad;

		//private methods vmt - also state
			self->vmt = eNEW(render_t_vmt);
			eCONSTRUCT(render_t_vmt, self->vmt);

	}
