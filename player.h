#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "tile.h"
#include "vector2.h"
//#include "shotgun.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player {
public:
    static const int DOT_WIDTH = 32;
    static const int DOT_HEIGHT = 32;

    static const int DOT_VEL = 10;

    Player();
    explicit Player(Texture* texture);

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

#endif //GAME_PLAYER_H
