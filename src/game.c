//INCLUDES
#include "game.h"
#include "snake.h"
#include "input.h"
#include "apple.h"
#include "text.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//GLOBAL VARIABLES
// - "g" as in "global"
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
GameState gameState;
ScreenInfo gScreenInfo;

uint64_t current_tick;
uint64_t last_tick;

//FUNCTIONS
// - helper functions
void error(char* text) {
    SDL_Log("ERROR: %s failed! - %s\n", text, SDL_GetError());
}

// - game functions
// - this functions is like the game.c's own main function
int startGame() {
    //just initialiazing everything and checking for errors.
    srand(time(NULL)); //seeding the rand, used in the apple.c/generatePosition();
    if (!gameInitialization()) {
        return 1;
    }
    if (!getMonitorSize()) {
        return 1;
    }
    if (!createWindow()) {
        return 1;
    }
    if (!createRenderer()) {
        return 1;
    }
    gameLoop();
    return 0;
}

void cleanUp() {
    //cleaning up after your code, never hurts :D
    if (gRenderer) {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = NULL;
    }
    if (gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

bool gameInitialization() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) || !TTF_Init()) {
        error("Game initialization");
        return false;
    }
    return true;
}

bool getMonitorSize() {
    //getting monitor size and initialiazing some variables!
    SDL_DisplayID *displays;
    const SDL_DisplayMode *displayMode;
    int count;

    displays = SDL_GetDisplays(&count);
    if (!displays) {
        error("No display found");
        return false;
    }
    displayMode = SDL_GetCurrentDisplayMode(displays[0]);
    if (!displayMode) {
        error("Getting display mode");
        return false;
    }
    gScreenInfo.monitorSizeX = displayMode->w;
    gScreenInfo.monitorSizeY = displayMode->h;
    gScreenInfo.windowSizeX = LOGICAL_WINDOW_SIZE_X;
    gScreenInfo.windowSizeY = LOGICAL_WINDOW_SIZE_Y;
    gScreenInfo.tileSize = TILE_SIZE;
    SDL_free(displays);
    return true;
}

bool createWindow() {
    gWindow = SDL_CreateWindow("Snake", gScreenInfo.monitorSizeX, gScreenInfo.monitorSizeY, SDL_WINDOW_FULLSCREEN);
    if (gWindow == NULL) {
        error("Window creation");
        return false;
    }
    return true;
}

bool createRenderer() {
    gRenderer = SDL_CreateRenderer(gWindow, NULL);
    if (gRenderer == NULL) {
        error("Renderer creation");
        return false;
    }
    //so always the game is at "640x480" for the retro feel!
    SDL_SetRenderLogicalPresentation(gRenderer, LOGICAL_WINDOW_SIZE_X, LOGICAL_WINDOW_SIZE_Y, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    return true;
}

//!!!MUST FREE THE ARRAY AFTERWARDS!!!
int* colorToRGB(Color color) {
    int rgb = 3; //3 AS IN R,G,B
    int *array = (int*)malloc(rgb * sizeof(int)); //!!!MUST FREE THE ARRAY AFTERWARDS!!!
    if (array == NULL) {
        error("Allocating memory in colorToRGB()");
        exit(1);
    }
    //JUST TURNING THE COLORS INTO THEIRS RGB
    switch (color) {
        case WHITE: //255, 255, 255
            array[0] = 255; array[1] = 255; array[2] = 255;
            break;
        case BLACK: //15, 15, 15
            array[0] = 15; array[1] = 15; array[2] = 15;
            break;
        case GRAY: //30, 30, 30
            array[0] = 30; array[1] = 30; array[2] = 30;
            break;
        case PURPLE: //128, 0, 128
            array[0] = 128; array[1] = 0; array[2] = 128;
            break;
        case RED: //255, 0, 0
            array[0] = 255; array[1] = 0; array[2] = 0;
            break;
        case LIGHTER_GREEN: //170, 215, 81
            array[0] = 170; array[1] = 215; array[2] = 81;
            break;
        case DARKER_GREEN: //162, 209, 73
            array[0] = 162; array[1] = 209; array[2] = 73;
            break;
        case NONE_COLOR:
            break;
    }
    return array;
}

void renderTile(SDL_FRect *tile, Color color, bool border, Color borderColor) {
    //made this function to fast-forward writing SDL_RenderRect
    int* colorArray = colorToRGB(color);
    //255 so it is not transparent
    SDL_SetRenderDrawColor(gRenderer, colorArray[0], colorArray[1], colorArray[2], 255);
    SDL_RenderFillRect(gRenderer, tile);
    if (border) {
        int* borderArray = colorToRGB(borderColor);
        SDL_SetRenderDrawColor(gRenderer, borderArray[0], borderArray[1], borderArray[2], 255);
        SDL_RenderRect(gRenderer, tile);
        free(borderArray);
    }
    free(colorArray);
}

void renderMap() {
    //just rendering the whole, map, tiles, snake and apples!
    Color tileColor;
    for (int col = 0; (float)col < gScreenInfo.windowSizeY / gScreenInfo.tileSize; col++) {
        for (int row = 0; (float)row < gScreenInfo.windowSizeX / gScreenInfo.tileSize; row++) {
            SDL_FRect tile = {(float)row * gScreenInfo.tileSize, (float)col * gScreenInfo.tileSize, gScreenInfo.tileSize, gScreenInfo.tileSize};
            if (row % 2 == 0 && col % 2 == 0 || row % 2 == 1 && col % 2 == 1) {
                tileColor = LIGHTER_GREEN;
            } else {
                tileColor = DARKER_GREEN;
            }
            renderTile(&tile, tileColor, false, GRAY);
            renderSnake(row, col);
        }
    }
    renderApple();
}

void renderScore() {
    char score[4]; //4 as in max digits, max score is 300, so 3 digits + '\0' :D
    sprintf(score, "%d", snake.points); //converting score(int) into a string
    renderText(score, WHITE, gScreenInfo.windowSizeX / 10.0f, (TextPosition){gScreenInfo.windowSizeX / 2.0f, gScreenInfo.windowSizeY / 6.0f});
}

void gamePlay() {
    //Game/loop logic
    //moving snake based on a set delays
    current_tick = SDL_GetTicks();
    if (current_tick - last_tick >= MOVE_DELAY) {
        snakeMove();
        last_tick = current_tick;
    }

    //checking collisions
    if (checkSnakeCollision()) {
        gameState = STATE_GAMEOVER;
    }
    if (checkAppleCollision()) {
        snake.points++;
        snake.length++;
        apple.spawned = false;
    }
    //checking if there is already an apple spawned
    if (!apple.spawned) {
        spawnApple();
    }
    renderMap();
}

void gameMenu() {
    TextPosition center = {gScreenInfo.windowSizeX / 2.0f, gScreenInfo.windowSizeY / 2.0f};
    renderText("SNAKE", WHITE, gScreenInfo.windowSizeX / 12.0f, (TextPosition){center.x, center.y / 2.0f});
    renderText("Press \"SPACE\" to play!", WHITE, gScreenInfo.windowSizeX / 32.0f, (TextPosition){center.x, center.y * 1.20f});
    renderText("Press \"ESCAPE\" to exit!", WHITE, gScreenInfo.windowSizeX / 32.0f, (TextPosition){center.x, center.y * 1.32f});
}

void gameOver() {
    TextPosition center = {gScreenInfo.windowSizeX / 2.0f, gScreenInfo.windowSizeY / 2.0f};
    renderText("GAME OVER", RED, gScreenInfo.windowSizeX / 10.0f, center);
    renderText("Press SPACE to restart", WHITE, gScreenInfo.windowSizeX / 32.0f,
               (TextPosition) {center.x, center.y * 1.3f});
}

void gameRestart() {
    //reinitializating stuff!
    snakeInitialization();
    appleInitialization();
    gameState = STATE_PLAYING;
    last_tick = SDL_GetTicks();
}

void gameLoop() {
    //function and variables initialization
    SDL_Event event;
    int delay = 16; //this means the game will run around 60 FPS

    gameState = STATE_MENU;

    snakeInitialization();
    appleInitialization();
    fontInitialization();
    last_tick = SDL_GetTicks();

    //the main game loop
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (!windowInput(&event)) {
                running = false;
            }
            if (gameState == STATE_MENU) {
                menuInput(&event);
            }
            if (gameState == STATE_PLAYING) {
                gameInput(&event);
            }
            if (gameState == STATE_GAMEOVER) {
                restartInput(&event);
            }
        }
        //Rendering
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        if (gameState == STATE_MENU) {
            gameMenu();
        }
        if (gameState == STATE_PLAYING) {
            gamePlay();
            renderScore();
        }
        if (gameState == STATE_GAMEOVER) {
            gameOver();
        }
        SDL_RenderPresent(gRenderer);
        SDL_Delay(delay);
    }
}
