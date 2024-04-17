#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H


#include "texture.h"
#include "tile.h"
#include "path.h"

class Enemy {
public:
    Enemy(Texture* texture, Path* path);
    void render(int camX, int camY);
    void move(const Dot &dot, const Map &map);
private:
    static const int ENEMY_VEL = 2;
    int mPosX, mPosY;
    Texture* texture;
    Path* path;

    void moveEnemyOnPath(const std::pair<int, int> &enemyCoordinate);

    bool
    playerIsCloseEnough(const std::pair<int *, int *> &enemyCoordinate,
                        const std::pair<int *, int *> &playerCoordinates) const;

    static bool
    playerIsCloseEnough(const std::pair<int, int> &enemyCoordinates, const std::pair<int, int> &playerCoordinates) ;

    bool
    playerIsVisible(const std::pair<int, int> &enemyCoordinate, const std::pair<int, int> &playerCoordinates, Map map);
};


#endif //GAME_ENEMY_H
