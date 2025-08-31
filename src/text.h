#ifndef SNAKE_TEXT_H
#define SNAKE_TEXT_H

//INCLUDES
#include "game.h"
#include <SDL3_ttf/SDL_ttf.h>

//DEFINED TYPES/MACROS
// - structs
typedef struct {
    float x;
    float y;
} TextPosition;

//GLOBAL VARIABLES
extern TTF_Font *font;
extern float defaultFontSize;

//FUNCTIONS
void fontInitialization();
void renderText(char* text, Color color, float size, TextPosition pos);

#endif //SNAKE_TEXT_H
