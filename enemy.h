#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H


#include "texture.h"
#include "tile.h"
#include "path.h"

class Enemy {
public:
    Enemy(Texture* texture, Path* path);
    void render(int camX, int camY);
    void move();
private:
    static const int ENEMY_VEL = 2;
    int mPosX, mPosY;
    Texture* texture;
    Path* path;
};


#endif //GAME_ENEMY_H
