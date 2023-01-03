#include "sdl2engine_render_pub.h"
#include "sdl2engine_render_class.h"

//opengl loader
#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "../utils.h"
#include "../io/sdl2engine_io.h"

#define SELF_TYPE sdl2engine_render_t

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
	void sdl2engine_render_t_initWindow(void * eOBJ)
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
			self->width,
			self->height,
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
* Initialise a quad
* @param void* eOBJ Self (class)
* @return SDL_Window
*/
	void sdl2engine_render_t_initQuad(void * eOBJ, uint32_t *vao, uint32_t *vbo, uint32_t *ebo)
	{
		//cast eOBJ back into class (NOT vmt!) type pointer
			eSELF(SELF_TYPE);

		// x, y, x, u, v
			float vertices[] = {
				0.5f, 0.5f, 0,0,0,
				0.5f, -0.5f, 0, 0, 1,
				-0.5f, -0.5f, 0, 1, 1,
				-0.5f, 0.5f, 0, 1, 0
			};

		uint32_t indices [] ={
			0, 1, 3,
			1, 2, 3
		};

		//store into state members
		glGenVertexArrays(1, vao);
		glGenBuffers(1, vbo);
		glGenBuffers(1, ebo);

		glBindVertexArray(*vao);

		glBindBuffer(GL_ARRAY_BUFFER, *vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//xyz
		glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 5*sizeof(float), NULL);
		glEnableVertexAttribArray(0);

		//uv
		glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3 * sizeof(float ) ));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);

	}

	void sdl2engine_render_t_initColorTexture(void * eOBJ, uint32_t *texture)
	{
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);

		uint8_t solid_white[4] = {255,255,255,255};
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, solid_white);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void sdl2engine_render_t_initShaders(void * eOBJ)
	{
		//cast eOBJ back into class (NOT vmt!) type pointer
			eSELF(SELF_TYPE);

		self->vmt->state.shader_default = self->vmt->shaderCreate(DIR_SHIFT"shaders/default.vert", DIR_SHIFT"shaders/default.frag");

		mat4x4_ortho(self->vmt->state.projection, 0, self->width, 0, self->height, -2, 2);

		glUseProgram(self->vmt->state.shader_default);
		glUniformMatrix4fv(
			glGetUniformLocation(self->vmt->state.shader_default, "projection"),
			1,
			GL_FALSE,
			&self->vmt->state.projection[0][0]
		);

	}

	uint32_t sdl2engine_render_t_shaderCreate(const char * path_vert, const char * path_frag)
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
	void sdl2engine_render_t_vmt_instantiate(void * eOBJ)
	{
		//cast eOBJ back into class vmt type pointer
			eSELF(sdl2engine_render_t_vmt);

		//define private methods
			self->initWindow = &sdl2engine_render_t_initWindow;
			self->initQuad = &sdl2engine_render_t_initQuad;
			self->initColorTexture = &sdl2engine_render_t_initColorTexture;
			self->initShaders = &sdl2engine_render_t_initShaders;
			self->shaderCreate = &sdl2engine_render_t_shaderCreate;

	}

//PUBLIC METHODS

/**
* Initialise the window, and quad values in render internal state
* @id sdl2engine_render_t_init
* @function init
* @param void* eOBJ self
* @param int widthHere window width
* @param int heightHere window height
* @return void
*/
	void sdl2engine_render_t_init(void * eOBJ, int widthHere, int heightHere)
	{
		eSELF(SELF_TYPE);

		//define props
			self->width = widthHere;
			self->height = heightHere;

		//actually create window
			self->vmt->initWindow(self);

		//init quad
			self->vmt->initQuad(self, &self->vmt->state.vao_quad, &self->vmt->state.vbo_quad, &self->vmt->state.ebo_quad);
			self->vmt->initShaders(self);
			self->vmt->initColorTexture(self, &self->vmt->state.texture_color);

	}

/**
* Begin Rendering a frame
* @return void
*/
	void sdl2engine_render_t_begin()
	{
		glClearColor(0.08f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

/**
* End Rendering a frame
* @param void* eOBJ self
* @return void
*/
	void sdl2engine_render_t_end(void * eOBJ)
	{
		eSELF(SELF_TYPE);
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
	void sdl2engine_render_t_quad(void * eOBJ, vec2 pos, vec2 size, vec4 color)
	{
		eSELF(SELF_TYPE);

		glUseProgram(self->vmt->state.shader_default);

		mat4x4 model;
		mat4x4_identity(model);

		mat4x4_translate(model, pos[0], pos[1], 0);
		mat4x4_scale_aniso(model, model, size[0], size[1], 1);

		glUniformMatrix4fv(glGetUniformLocation(self->vmt->state.shader_default, "model"), 1, GL_FALSE, &model[0][0]);
		glUniform4fv(glGetUniformLocation(self->vmt->state.shader_default, "color"), 1, color);

		glBindVertexArray(self->vmt->state.vao_quad);

		glBindTexture(GL_TEXTURE_2D, self->vmt->state.texture_color);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		glBindVertexArray(0);

	}

/**
* Instantiate Render object
* @param void* eOBJ self
* @return void
*/
	void sdl2engine_render_t_instantiate(void * eOBJ)
	{
		eSELF(SELF_TYPE);

		//public methods
			self->init = &sdl2engine_render_t_init;
			self->begin = &sdl2engine_render_t_begin;
			self->end = &sdl2engine_render_t_end;
			self->quad = &sdl2engine_render_t_quad;

		//private methods vmt - also state
			self->vmt = eNEW(sdl2engine_render_t_vmt);
			eCONSTRUCT(sdl2engine_render_t_vmt, self->vmt);

	}
