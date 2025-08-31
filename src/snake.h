#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

//INCLUDES
#include "game.h"
#include <stdint.h>
#include <SDL3/SDL.h>
#include <stdlib.h>
//DEFINED TYPES/MACROS
// - enums
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE_DIR,
} Direction;
// - structs
typedef struct {
   Direction direction;
   uint8_t length;
   uint16_t body[400][2];
   uint8_t points;
} Snake;

//GLOBAL VARIABLES
extern Snake snake;

//FUNCTIONS
void snakeInitialization();
void snakeMove();
bool checkSnakeCollision();
void renderSnake(int row, int col);

#endif //SNAKE_SNAKE_H
