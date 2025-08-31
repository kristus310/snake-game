//INCLUDES
#include "snake.h"
#include "game.h"
#include <SDL3/SDL.h>

//GLOBAL VARIABLES
Snake snake;

//FUNCTIONS
void snakeInitialization() {
    //just setting starter/default info
    snake.points = 0;
    snake.direction = RIGHT;
    snake.length = 3;
    int startX = 10;
    int startY = 10;
    for (int i = 0; i < snake.length; i++) {
        snake.body[i][0] = startX - i;
        snake.body[i][1] = startY;
    }
}

void snakeMove() {
    //moving body
    for (int i = snake.length; i > 0; i--) {
        snake.body[i][0] = snake.body[i - 1][0];
        snake.body[i][1] = snake.body[i - 1][1];
    }

    //moving head
    switch (snake.direction) {
        case UP:
            snake.body[0][1]--;
            break;
        case DOWN:
            snake.body[0][1]++;
            break;
        case LEFT:
            snake.body[0][0]--;
            break;
        case RIGHT:
            snake.body[0][0]++;
            break;
        case NONE_DIR:
            break;
    }
}

bool checkSnakeCollision() {
    //snake + wall collision
    if (snake.body[0][0] >= (int)gScreenInfo.windowSizeX / (int)gScreenInfo.tileSize || snake.body[0][0] < 0) {
        snake.direction = NONE_DIR;
        return true;
    }
    if (snake.body[0][1] >= (int)gScreenInfo.windowSizeY / (int)gScreenInfo.tileSize || snake.body[0][1] < 0) {
        snake.direction = NONE_DIR;
        return true;
    }
    //snake's own collision
    for (int i = 3; i < snake.length; i++) {
        if (snake.body[0][0] == snake.body[i][0] && snake.body[0][1] == snake.body[i][1]) {
            return true;
        }
    }
    return false;
}

void renderSnake(int row, int col) {
    //again just rendering the snake, nothing more
    for (int i = 0; i < snake.length; i++) {
        if (snake.body[i][0] == row && snake.body[i][1] == col) {
            SDL_FRect body = {(float)row * gScreenInfo.tileSize, (float)col * gScreenInfo.tileSize, gScreenInfo.tileSize, gScreenInfo.tileSize};
            if (i == 0) {
                //snake's head!
                renderTile(&body, BLACK, false, NONE_COLOR);
            } else {
                //and body
                renderTile(&body, GRAY, false, NONE_COLOR);
            }
        }
    }
}