#include <stdio.h>

//opengl loader
#include <glad/glad.h>

//definition below needed to stop SDL lib making "main" a macro.
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <stdbool.h>

int main(int argc, char *argv[])
{

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Could not init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Window *window = SDL_CreateWindow(
		"SDL GEngine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_OPENGL
	);

	if(!window){
		printf("Could not init SDL window: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_GL_CreateContext(window);
	if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
		printf("Could not load GL: %s\n", SDL_GetError());
		exit(1);
	}

	puts("OpenGL Loaded");
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	bool shouldQuit = false;

	while(!shouldQuit){

		SDL_Event event;

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					shouldQuit = true;
					break;
			}
		}

	}

	return 0;
}
