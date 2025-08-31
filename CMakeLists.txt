cmake_minimum_required(VERSION 4.0)
project(snake C)

set(CMAKE_C_STANDARD 11)

set(SDL3_PATH "D:/Libraries/SDL3/x86_64-w64-mingw32")
include_directories(${SDL3_PATH}/include)
link_directories(${SDL3_PATH}/lib)

set(SDL3_TTF_PATH "D:/Libraries/SDL3_ttf/x86_64-w64-mingw32")
include_directories(${SDL3_TTF_PATH}/include)
link_directories(${SDL3_TTF_PATH}/lib)

add_executable(snake src/main.c
        src/game.c
        src/game.h
        src/snake.c
        src/snake.h
        src/input.c
        src/input.h
        src/apple.c
        src/apple.h
        src/text.c
        src/text.h
)

target_link_libraries(snake SDL3 SDL3_ttf)