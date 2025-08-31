//INCLUDES
#include "text.h"
#include "game.h"
#include <SDL3_ttf/SDL_ttf.h>

//GLOBAL VARIABLES
TTF_Font *font;
float defaultFontSize;

//FUNCTIONS
void fontInitialization() {
    //just setting starter/default info
    defaultFontSize = 24;
    //list of possible paths
    const char* fontPaths[] = {
            "../assets/fonts/font.ttf",
            "./assets/fonts/font.ttf",
            "assets/fonts/font.ttf",
            "../font.ttf",
            "./font.ttf",
            NULL
    };

    font = NULL;
    for (int i = 0; fontPaths[i] != NULL; i++) {
        font = TTF_OpenFont(fontPaths[i], defaultFontSize);
        if (font) {
            break;
        }
    }
    if (!font) {
        error("Font initialization");
    }
}

void renderText(char* text, Color color, float size, TextPosition pos) {
    //..again just rendering the text! :D
    TTF_SetFontSize(font, size);
    int* colorArray = colorToRGB(color);
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, 0, (SDL_Color){colorArray[0], colorArray[1], colorArray[2], 255});
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    float textWidth = (float)textSurface->w;
    float textHeight = (float)textSurface->h;

    pos.x -= (textWidth / 2.0f);
    pos.y -= (textHeight / 2.0f);

    SDL_FRect textRect = {pos.x, pos.y, textWidth, textHeight};
    SDL_RenderTexture(gRenderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
    SDL_DestroySurface(textSurface);
    free(colorArray);
    TTF_SetFontSize(font, defaultFontSize);
}