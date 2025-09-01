cmake_minimum_required(VERSION 4.0)
project(snake C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Works with vcpkg (Windows) or system packages (Linux/macOS)
find_package(SDL3 REQUIRED CONFIG COMPONENTS SDL3)
find_package(SDL3_ttf REQUIRED CONFIG)

set(SOURCES
        src/main.c
        src/game.c
        src/snake.c
        src/input.c
        src/apple.c
        src/text.c
)
set(HEADERS
        src/game.h
        src/snake.h
        src/input.h
        src/apple.h
        src/text.h
)

add_executable(snake ${SOURCES} ${HEADERS})

target_include_directories(snake PRIVATE src)
target_link_libraries(snake PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)