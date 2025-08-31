//INCLUDES
#include "input.h"
#include "snake.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

//FUNCTIONS
//input of the whole "game", so the "quit button" and ESC, for quiting
bool windowInput(SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return false;
    }
    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) {
        return false;
    }
    return true;
}

//the other functions speak for themselves, in their name :D

void menuInput(SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_SPACE) {
        gameState = STATE_PLAYING;
    }
}

void gameInput(SDL_Event *event) {
    Direction direction = keyboardInput(event);
    if (direction != NONE_DIR) {
        snake.direction = direction;
    }
}

void restartInput(SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_SPACE) {
        gameRestart();
    }
}

Direction keyboardInput(SDL_Event *event) {
    //overly complicated snake movement lol
    if (event->type != SDL_EVENT_KEY_DOWN) {
        return NONE_DIR;
    }

    Direction newDirection = NONE_DIR;
    if (event->key.key == SDLK_A || event->key.key == SDLK_LEFT) {
        newDirection = LEFT;
    }
    else if (event->key.key == SDLK_D || event->key.key == SDLK_RIGHT) {
        newDirection = RIGHT;
    }
    else if (event->key.key == SDLK_W || event->key.key == SDLK_UP) {
        newDirection = UP;
    }
    else if (event->key.key == SDLK_S || event->key.key == SDLK_DOWN) {
        newDirection = DOWN;
    }

    if (newDirection != NONE_DIR) {
        switch (snake.direction) {
            case UP:
                if (newDirection == DOWN) {
                    return NONE_DIR;
                }
                break;
            case DOWN:
                if (newDirection == UP) {
                    return NONE_DIR;
                }
                break;
            case LEFT:
                if (newDirection == RIGHT) {
                    return NONE_DIR;
                }
                break;
            case RIGHT:
                if (newDirection == LEFT) {
                    return NONE_DIR;
                }
            break;
            case NONE_DIR:
                break;
        }
    }

    return newDirection;
}