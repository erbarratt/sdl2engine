cmake_minimum_required(VERSION 3.23)
project(sdl2engine C)

set(CMAKE_C_STANDARD 99)

#required to get the sdl2 cmake file
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/Users/elbaz/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/222.4345.21/bin/mingw/x86_64-w64-mingw32/lib/cmake/SDL2")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

#define all source files
set(SOURCE_FILES main.c lib/glad/src/glad.c)

#set include dir's so includes work in IDE
include_directories(lib/glad/include)

add_executable(sdl2engine ${SOURCE_FILES})

#link to SDL library
target_link_libraries(sdl2engine ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)
