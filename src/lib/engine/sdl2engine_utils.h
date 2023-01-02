#ifndef SDL2ENGINE_SDL2ENGINE_UTILS_H
#define SDL2ENGINE_SDL2ENGINE_UTILS_H

#include <stdio.h>

#define ERROR_EXIT(...) fprintf(stderr, __VA_ARGS__); exit(1)
#define ERROR_RETURN(r, ...) fprintf(stderr, __VA_ARGS__); return r

#endif //SDL2ENGINE_SDL2ENGINE_UTILS_H
