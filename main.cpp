#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
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
#include "button.h"

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 800;

bool init();

bool loadMedia();

void close();

bool isAnyEnemyAlive(std::vector<Enemy*> enemies);

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
Texture gRestartTextTexture;
Texture gStartGameTextTexture;
Texture gScoreTextTexture;
Texture gSemiTransparentTexture;
TTF_Font* gFont = nullptr;
SDL_Color blackText = {0, 0, 0, 255 };
SDL_Color whiteText = {255, 255, 255, 255 };
Timer gameStartedTimer = Timer();

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

        gWindow = SDL_CreateWindow("SDG Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
                if (TTF_Init() == -1) {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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
                gStartGameTextTexture.setRenderer(renderer);
                gRestartTextTexture.setRenderer(renderer);
                gScoreTextTexture.setRenderer(renderer);
                gSemiTransparentTexture.setRenderer(renderer);
            }
        }
    }

    return success;
}

bool loadMedia() {
    bool success = true;

    gFont = TTF_OpenFont("assets/quadriana.ttf", 80);

    if (!gStartGameTextTexture.loadFromRenderedText("Start", blackText, gFont)) {
        printf( "Unable to load gStartGameTextTexture!\n" );
    }

    if (!gRestartTextTexture.loadFromRenderedText("Restart", blackText, gFont)) {
        printf( "Unable to load gRestartTextTexture!\n" );
    }


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

    if (!gSemiTransparentTexture.createSemiTransparentTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 178)) {
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
    gShotgunSpreadTexture.free();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

bool isAnyEnemyAlive(std::vector<Enemy*> enemies) {
    for (auto enemy : enemies) {
        if (enemy->isAlive) {
            return true;
        }
    }
    return false;
}

int calculateScore(float timerTicksInSeconds) {
    int maxScore = 10000;
    if (timerTicksInSeconds <= 0) {
        return maxScore;
    }
    return maxScore / timerTicksInSeconds;
}

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            bool quit = false;
            bool gameStarted = false;
            bool gameFinished = false;

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
            Shotgun shotgun = Shotgun(&gShotgunSpreadTexture, &enemies, &player, map, &camera);
            auto cursor = Cursor(&gCursorTexture);
            auto startButton = Button(&gStartGameTextTexture, SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 50, 500, 100);
            auto restartButton = Button(&gRestartTextTexture, SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 + 100, 500, 100);

            while (!quit) {
                while (SDL_PollEvent( &e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    if (gameStarted && !gameFinished) {
                        player.handleEvent(e);
                        shotgun.handleEvent(e);
                    } else if (gameFinished) {
                        restartButton.handleEvent(e);
                    } else {
                        startButton.handleEvent(e);
                    }
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
                    shotgun.renderEnemyShooting(camera.x, camera.y, enemy);
                    if (enemy->canShootPlayer(player)) {
                        player.kill(&bloodEffectCollection, enemy->getPosX(), enemy->getPosY());
                        shotgun.markEnemyThatShotPlayer(enemy);
                    }
                }
                player.render(camera.x, camera.y);
                shotgun.render(camera.x, camera.y);

                if (!isAnyEnemyAlive(enemies)) {
                    gameFinished = true;
                    gameStartedTimer.pause();
                }
                if (gameFinished) {
                    player.kill();
                    gSemiTransparentTexture.render(0, 0);
                    int score = calculateScore(gameStartedTimer.getTicks() / 1000.0f);
                    if (!gScoreTextTexture.loadFromRenderedText("SCORE:" + std::to_string(score), whiteText, gFont)) {
                        printf( "Unable to load gStartGameTextTexture!\n" );
                    }
                    gScoreTextTexture.render(SCREEN_WIDTH / 2 - (gScoreTextTexture.getWidth() / 2),
                                             SCREEN_HEIGHT / 2 - (gScoreTextTexture.getHeight() / 2) - 100);
                    restartButton.render();
                    if (restartButton.isClicked()) {
                        player.revive();
                        for (auto enemy : enemies) {
                            enemy->revive();
                        }
                        bloodEffectCollection.bloodEffects.clear();
                        restartButton.reset();
                        gameStartedTimer.stop();
                        gameStartedTimer.start();
                        gameFinished = false;
                    }
                }
                if (!gameStarted) {
                    gSemiTransparentTexture.render(0, 0);
                    startButton.render();
                    if (startButton.isClicked()) {
                        player.isAlive = true;
                        gameStarted = true;
                        startButton.reset();
                        gameStartedTimer.stop();
                        gameStartedTimer.start();
                    }
                }

                cursor.render();
                SDL_RenderPresent(renderer);
            }
        }
    }

    close();

    return 0;
}