#include <stdio.h>
//definition below needed to stop SDL lib making "main" a macro.
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
	printf("Hello, World!\n");
	return 0;
}
