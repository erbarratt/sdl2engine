#ifndef SDL2ENGINE_SDL2ENGINE_IO_H
#define SDL2ENGINE_SDL2ENGINE_IO_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct file {
	char *data;
	size_t len;
	bool is_valid;
} File;

File io_file_read(const char *path);
int io_file_write(void *buffer, size_t size, const char *path);

#endif //SDL2ENGINE_SDL2ENGINE_IO_H
