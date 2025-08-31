#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

//INCLUDES
#include "snake.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

//DEFINED TYPES/MACROS
// - defines
#define LOGICAL_WINDOW_SIZE_X 640
#define LOGICAL_WINDOW_SIZE_Y 480
#define TILE_SIZE 32
#define MOVE_DELAY 100
// - enums
typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAMEOVER,
} GameState;

typedef enum {
    BLACK,
    WHITE,
    GRAY,
    PURPLE,
    RED,
    LIGHTER_GREEN,
    DARKER_GREEN,
    NONE_COLOR,
} Color;
// - structs
typedef struct {
    int monitorSizeX;
    int monitorSizeY;
    float windowSizeX;
    float windowSizeY;
    float tileSize;
} ScreenInfo;

//GLOBAL VARIABLES
extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern GameState gameState;
extern ScreenInfo gScreenInfo;

extern uint64_t current_tick;
extern uint64_t last_tick;
//FUNCTIONS
// - helper functions
void error(char *text);
// - game functions
int startGame();
void cleanUp();
bool gameInitialization();
bool getMonitorSize();
bool createWindow();
bool createRenderer();
int* colorToRGB(Color color);
void renderTile(SDL_FRect *tile, Color color, bool border, Color borderColor);
void renderMap();
void renderScore();
void gamePlay();
void gameMenu();
void gameOver();
void gameRestart();
void gameLoop();

#endif //SNAKE_GAME_H
