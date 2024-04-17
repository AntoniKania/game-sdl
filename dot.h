#ifndef GAME_DOT_H
#define GAME_DOT_H

#include "tile.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Dot {
public:
    static const int DOT_WIDTH = 32;
    static const int DOT_HEIGHT = 32;

    static const int DOT_VEL = 10;

    Dot();
    explicit Dot(Texture* texture);

    void handleEvent(SDL_Event& e);

    void move(const std::vector<Tile>& tiles, const int& screenWidth, const int& screenHeight);

    void render(int camX, int camY);

    int getPosX() const;
    int getPosY() const;

private:
    int mPosX, mPosY;
    int mVelX, mVelY;
    Texture* texture;

    bool isColliding(const std::vector<Tile>& tiles);
};

#endif //GAME_DOT_H
