#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "dot.h"
#include "map.h"
#include "camera.h"
#include "enemy.h"

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

bool init();

bool loadMedia();

void close();

SDL_Window* gWindow = NULL;

SDL_Renderer* renderer = NULL;

Texture gDotTexture;
Texture gGrayTexture;
Texture gRedTexture;
Texture gEnemyTexture;
Map map;

bool init() {
    bool success = true;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if (renderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!( IMG_Init( imgFlags ) & imgFlags)) {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                gRedTexture.setRenderer(renderer);
                gGrayTexture.setRenderer(renderer);
                gDotTexture.setRenderer(renderer);
                gEnemyTexture.setRenderer(renderer);
            }
        }
    }

    return success;
}

bool loadMedia() {
    bool success = true;

    if (!gDotTexture.loadFromFile( "assets/dot.png")) {
        printf("Failed to load dot texture!\n");
        success = false;
    }

    if (!gGrayTexture.loadFromFile("assets/gray.png")) {
        printf("Failed to load gray texture!\n");
        success = false;
    }

    if (!gRedTexture.loadFromFile("assets/red.png")) {
        printf("Failed to load red texture!\n");
        success = false;
    }

    if (!gEnemyTexture.loadFromFile("assets/enemy.png")) {
        printf("Failed to load enemy texture!\n");
        success = false;
    }
    map.load(&gGrayTexture, &gRedTexture);

    return success;
}

void close() {
    gDotTexture.free();
    gGrayTexture.free();
    gRedTexture.free();
    gEnemyTexture.free();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            bool quit = false;

            SDL_Event e;

            Dot dot = Dot(&gDotTexture);
            Path pathEnemy1 = Path(map);
            Enemy enemy = Enemy(&gEnemyTexture, &pathEnemy1);
            Camera camera;

            while (!quit) {
                while (SDL_PollEvent( &e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    dot.handleEvent(e);
                }
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                dot.move(map.getTiles(), 3840, 2560);
                enemy.move();
                camera.setCamera(dot);
                map.draw(&camera);
                enemy.render(camera.x, camera.y);
                dot.render(camera.x, camera.y);

                SDL_RenderPresent(renderer);
            }
        }
    }

    close();

    return 0;
}