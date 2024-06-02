# Top-Down Shooter Game Simulation

## Overview

This project is part of the "Game Theory and Simulations" course. The objective was to implement the "simulation" aspect in the form of a 2D game. The game developed is a top-down shooter featuring collision detection, line of sight, and shooting logic (including angle calculations, distance measurements, and visibility checks). The game runs on both Linux and Windows and can be compiled using either Makefile or CMake.

## Features

- **Collision Detection**: Implements robust collision detection to ensure objects interact realistically.
- **Line of Sight**: Uses algorithms to determine the player's visibility and field of view.
- **Shooting Logic**: Calculates shooting angles, distances, and checks for visibility to simulate realistic shooting mechanics.
- **Custom Assets**: All game assets, were created by me.

## Requirements

- C++ compiler (g++ or similar)
- SDL2 library

## Compilation and Execution

### Using Makefile

1. **Linux**:
    ```bash
    make
    ./game
    ```
2. **Windows**: checkout the `windows_port` branch, then:
    ```bash
    mingw32-make
    .\game.exe
    ```

## Controls

- **W/A/S/D**: Move the player up/left/down/right.
- **Mouse**: Aim and shoot.

## Screenshots
![image](https://github.com/AntoniKania/game-sdl/assets/87483058/3aeda842-b2c6-4d9c-846b-bc38c49e05a7)

![image](https://github.com/AntoniKania/game-sdl/assets/87483058/96acd0eb-4b87-412f-9624-60be6bce065e)

![image](https://github.com/AntoniKania/game-sdl/assets/87483058/9ddc851d-a17f-4b40-b729-5c69fe5ba303)

![image](https://github.com/AntoniKania/game-sdl/assets/87483058/c21b32db-2750-49b6-a2f8-59750d2ca70d)




