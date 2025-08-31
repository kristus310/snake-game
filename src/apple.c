//INCLUDES
#include "apple.h"
#include "game.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//GLOBAL VARIABLES
Apple apple;

//FUNCTIONS
// - helper functions
void generateApplePosition() {
    //i know rand isn't the best way to generate a number, but for this simple number, it is more than enough
    apple.x = rand() % ((int)gScreenInfo.windowSizeX / (int)gScreenInfo.tileSize);
    apple.y = rand() % ((int)gScreenInfo.windowSizeY / (int)gScreenInfo.tileSize);
}

// - game functions
void appleInitialization() {
    //just setting starter/default info
    apple.spawned = false;
}

void renderApple() {
    SDL_FRect appleTile = {(float)apple.x * gScreenInfo.tileSize, (float)apple.y * gScreenInfo.tileSize, gScreenInfo.tileSize, gScreenInfo.tileSize};
    renderTile(&appleTile, RED, false, NONE_COLOR);
}

void spawnApple() {
    //spawning the apple and making sure it isn't spawning in the snake :D
    bool inSnake;
    do {
        generateApplePosition();
        inSnake = false;

        for (int i = 0; i < snake.length; i++) {
            if (apple.x == snake.body[i][0] && apple.y == snake.body[i][1]) {
                inSnake = true;
                break;
            }
        }
    } while (inSnake);
    apple.spawned = true;
}

bool checkAppleCollision() {
    //checking if snake hits the apple!
    if (snake.body[0][0] == apple.x && snake.body[0][1] == apple.y) {
        return true;
    }
    return false;
}