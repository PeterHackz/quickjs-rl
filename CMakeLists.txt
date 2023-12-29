set(CMAKE_C_COMPILER gcc)

# cmake . -G "MinGW Makefiles"

cmake_minimum_required(VERSION 3.10)
project(RaylibApp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES
    "src/*.c"
)

include_directories(include)

link_directories(
    ./raylib
    ./quickjs
)

add_executable(app ${SOURCES})

set_target_properties(app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)

target_link_libraries(app raylib quickjs pthread opengl32 gdi32 winmm m)

if(WIN32)
    set_target_properties(app PROPERTIES LINK_FLAGS "-static")
    set_target_properties(app PROPERTIES COMPILE_FLAGS -g)
    target_compile_definitions(app PRIVATE CONFIG_BIGNUM)
  #  target_link_options(app PRIVATE -mwindows)
endif()