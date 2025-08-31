#ifndef SNAKE_INPUT_H
#define SNAKE_INPUT_H

//INCLUDES
#include "snake.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

//FUNCTIONS
bool windowInput(SDL_Event *event);
void menuInput(SDL_Event *event);
void gameInput(SDL_Event *event);
void restartInput(SDL_Event *event);
Direction keyboardInput(SDL_Event *event);

#endif //SNAKE_INPUT_H
