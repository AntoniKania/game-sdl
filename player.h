#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "tile.h"
#include "vector2.h"
#include "blood_effect.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player {
public:
    static const int DOT_WIDTH = 64;
    static const int DOT_HEIGHT = 64;

    static const int DOT_VEL = 10;

    explicit Player(Texture* texture);

    void handleEvent(SDL_Event& e);
    void move(const std::vector<Tile>& tiles, const int& screenWidth, const int& screenHeight);
    void kill(BloodEffectCollection *bloodEffectCollection, int shooterPosX, int shooterPosY);
    void render(int camX, int camY);
    bool isAlive;

    int getPosX() const;
    int getPosY() const;

private:
    int mPosX, mPosY;
    int mVelX, mVelY;
    double previousAngle;
    Texture* texture;
    bool isColliding(const std::vector<Tile>& tiles);
    double calculateAngle(int mousePosX, int mousePosY);
};

#endif //GAME_PLAYER_H
