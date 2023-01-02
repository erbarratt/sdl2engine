cmake_minimum_required(VERSION 3.23)
project(sdl2engine C)

set(CMAKE_C_STANDARD 99)

#required to get the sdl2 cmake file
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/Program Files/JetBrains/CLion 2022.3.1/bin/mingw/x86_64-w64-mingw32/lib/cmake/SDL2")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

#define all source files
set(SOURCE_FILES src/main.c src/lib/glad/src/glad.c src/lib/engine/sdl2engine_types.h src/lib/engine/sdl2engine_utils.h src/lib/eOOPc.h src/lib/engine/global/sdl2engine_global_class.c src/lib/engine/global/sdl2engine_global_class.h src/lib/engine/render/sdl2engine_render_pub.h src/lib/engine/linmath.h src/lib/engine/render/sdl2engine_render_class.c src/lib/engine/render/sdl2engine_render_class.h src/lib/engine/global/sdl2engine_global_pub.h src/lib/engine/io/sdl2engine_io.c src/lib/engine/io/sdl2engine_io.h src/lib/engine/utils.h src/lib/engine/utils.h)

#set include dir's so includes work in IDE
include_directories(src/lib/glad/include)

add_executable(sdl2engine ${SOURCE_FILES})

#link to SDL library
target_link_libraries(sdl2engine ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)
