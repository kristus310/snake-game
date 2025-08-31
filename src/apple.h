#ifndef SNAKE_APPLE_H
#define SNAKE_APPLE_H

//INCLUDES
#include <stdbool.h>
#include <stdint.h>

//DEFINED TYPES/MACROS
// - structs
typedef struct {
    uint8_t x;
    uint8_t y;
    bool spawned;
} Apple;

//GLOBAL VARIABLES
extern Apple apple;

//FUNCTIONS
// - helper functions
void generateApplePosition();
// - game functions
void appleInitialization();
void renderApple();
void spawnApple();
bool checkAppleCollision();

#endif //SNAKE_APPLE_H
