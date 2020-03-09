project( chip_8_emulator )

cmake_minimum_required(VERSION 3.10.2)

include_directories( include )

set( MY_CPP_FILES 
    src/main.cpp
    src/include/chip8.cpp
    src/include/chip8.hpp)

add_executable( chip8_emulator ${MY_CPP_FILES} )

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(chip8_emulator ${SDL2_LIBRARIES})
