#include "game.h"
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]) {
    //SDL3 needs argc and argv, but I am not using them, so I just "void" them
    (void) argc; (void) argv;

    //Starting game and before ending the game, I clean up everything
    int code = startGame();
    cleanUp();
    return code;
}
