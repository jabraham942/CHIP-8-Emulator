project( chip_8_emulator )

cmake_minimum_required(VERSION 3.10.2)

# set your include directories (if you have any)
include_directories( include )

# tell cmake what what are your source files
set( MY_CPP_FILES 
    src/main.cpp
    src/include/chip8.cpp
    src/include/chip8.hpp
    src/include/utils.cpp
    src/include/utils.hpp)

# if you are creating an executable then do so like this
# note that ${MY_CPP_FILES} will replace it with its content
add_executable( chip8_emulator ${MY_CPP_FILES} )

# if you instead want a library, do it like so
#add_library( myStaticLib STATIC ${MY_CPP_FILES} ) # create a static library
#add_library( mySharedLib SHARED ${MY_CPP_FILES} ) # create a shared library




INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(chip8_emulator ${SDL2_LIBRARIES})
