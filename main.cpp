#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "player.h"
#include "tile.h"
#include "map.h"
#include "camera.h"
#include "enemy.h"
#include "shotgun.h"
#include "cursor.h"
#include "blood_effect.h"

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

bool init();

bool loadMedia();

void close();

SDL_Window* gWindow = NULL;

SDL_Renderer* renderer = NULL;

Texture gDotTexture;
Texture gGroundTexture;
Texture gTreeTexture;
Texture gEnemyTexture;
Texture gCursorTexture;
Texture gBloodPuddleSprite;
Texture gBloodSpreadTexture;
Texture gShotgunSpreadTexture;
Map map;

bool init() {
    bool success = true;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear bloodPuddleTexture filtering not enabled!");
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
                gTreeTexture.setRenderer(renderer);
                gGroundTexture.setRenderer(renderer);
                gDotTexture.setRenderer(renderer);
                gEnemyTexture.setRenderer(renderer);
                gCursorTexture.setRenderer(renderer);
                gBloodPuddleSprite.setRenderer(renderer);
                gBloodSpreadTexture.setRenderer(renderer);
                gShotgunSpreadTexture.setRenderer(renderer);
            }
        }
    }

    return success;
}

bool loadMedia() {
    bool success = true;

    if (!gDotTexture.loadFromFile( "assets/player.png")) {
        printf("Failed to load player!\n");
        success = false;
    }

    if (!gGroundTexture.loadFromFile("assets/ground.png")) {
        printf("Failed to load gray bloodPuddleTexture!\n");
        success = false;
    }

    if (!gTreeTexture.loadFromFile("assets/tree.png")) {
        printf("Failed to load tree!\n");
        success = false;
    }

    if (!gEnemyTexture.loadFromFile("assets/deer.png")) {
        printf("Failed to load enemy bloodPuddleTexture!\n");
        success = false;
    }

    if (!gCursorTexture.loadFromFile("assets/cursor.png")) {
        printf("Failed to load cursor bloodPuddleTexture!\n");
        success = false;
    }

    if (!gBloodPuddleSprite.loadFromFile("assets/blood_puddle_sprite.png")) {
        printf("Failed to load blood_puddle_sprite bloodPuddleTexture!\n");
        success = false;
    }

    if (!gBloodSpreadTexture.loadFromFile("assets/blood_spread.png")) {
        printf("Failed to load blood_spread bloodPuddleTexture!\n");
        success = false;
    }

    if (!gShotgunSpreadTexture.loadFromFile("assets/spread.png")) {
        printf("Failed to load gShotgunSpreadTexture!\n");
        success = false;
    }

    map.load(&gGroundTexture, &gTreeTexture);

    return success;
}

void close() {
    gDotTexture.free();
    gGroundTexture.free();
    gTreeTexture.free();
    gEnemyTexture.free();
    gBloodSpreadTexture.free();
    gBloodPuddleSprite.free();

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
            SDL_ShowCursor(0);

            BloodEffectCollection bloodEffectCollection = BloodEffectCollection(&gBloodPuddleSprite, &gBloodSpreadTexture);
            Path pathEnemy1 = Path(map, TileType::PATH_ENEMY_1);
            Path pathEnemy2 = Path(map, TileType::PATH_ENEMY_2);
            Path pathEnemy3 = Path(map, TileType::PATH_ENEMY_3);
            Enemy enemy1 = Enemy(&gEnemyTexture, &map, &pathEnemy1, &bloodEffectCollection);
            Enemy enemy2 = Enemy(&gEnemyTexture, &map, &pathEnemy2, &bloodEffectCollection);
            Enemy enemy3 = Enemy(&gEnemyTexture, &map, &pathEnemy3, &bloodEffectCollection);
            std::vector<Enemy*> enemies = {&enemy1, &enemy2, &enemy3};
            Player player = Player(&gDotTexture);
            Camera camera;
            Shotgun shotgun = Shotgun(&enemies, &player, map, &camera);
            auto cursor = Cursor(&gCursorTexture);

            while (!quit) {
                while (SDL_PollEvent( &e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    player.handleEvent(e);
                    shotgun.handleEvent(e);
                }
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                camera.setCamera(player);
                map.draw(&camera);
                bloodEffectCollection.renderBloodEffects(camera.x, camera.y);
                player.move(map.getTiles(), 3840, 2560);
                for (auto enemy : enemies) {
                    enemy->move(player);
                    enemy->render(camera.x, camera.y);
                    if (enemy->canShootPlayer(player)) {
                        player.kill(&bloodEffectCollection, enemy->getPosX(), enemy->getPosY());
                    }
                }
                player.render(camera.x, camera.y);

                cursor.render();
                SDL_RenderPresent(renderer);
            }
        }
    }

    close();

    return 0;
}