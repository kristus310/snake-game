# Snake Game

A classic Snake game coded in **C** using **SDL3**, featuring **retro-style/user-responsive** graphics and **smooth** gameplay.
## Features

- **Classic Snake Gameplay**: Control a growing snake to eat apples and avoid collisions
- **Super responsive graphics**: Works on every screen, it calculates every object's size based on the user's screen size
- **Retro Graphics**: 640x480 resolution with a tiled, retro-inspired visual style
- **Smooth Controls**: WASD or arrow key movement with collision prevention

## Future
- **Sounds effects & music**: I plan to add SDL3_mixer for sound effects and music, for better user experience
- **Difficulties**: Bigger and smaller boards... faster and slower snake... etc!
- **And much more!**

## Controls

### Menu
- **SPACE**: Start the game
- **ESCAPE**: Exit the game

### Gameplay
- **W / UP ARROW**: Move up
- **S / DOWN ARROW**: Move down
- **A / LEFT ARROW**: Move left
- **D / RIGHT ARROW**: Move right
- **ESCAPE**: Exit the game

### Game Over
- **SPACE**: Restart the game

## Screenshots
![The main menu](screenshots/menu.png)
![The gameplay](screenshots/game_play.png)
![The ame over screen](screenshots/game_over.png)

## Requirements

- **SDL3**: Main graphics and input library
- **SDL3_ttf**: Text rendering library
- **C Compiler**: GCC, Clang, or MSVC
- **Font File**: TTF font file for text rendering

## Building

### Prerequisites

Make sure you have SDL3 and SDL3_ttf installed on your system:

```bash
# Ubuntu/Debian
sudo apt-get install libsdl3-dev libsdl3-ttf-dev

# macOS (with Homebrew)
brew install sdl3 sdl3_ttf

# Windows
# Download SDL3 and SDL3_ttf development libraries from libsdl.org or through vcpkg package manager (recommended)