#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H


#include "texture.h"
#include "map.h"
#include "path.h"
#include "vector2.h"

class Enemy {
public:
    bool isAlive;
    Enemy(Texture* texture, Map* map, Path* path);
    void render(int camX, int camY);
    void move(const Dot &dot, const Map &map);
    void kill();
private:
    static const int ENEMY_VEL = 2;
    int mPosX, mPosY;
    Texture* texture;
    Path* path;
    Map* map;

    void moveEnemyOnPath(const std::pair<int, int> &enemyCoordinate);

    static bool
    playerIsCloseEnough(const std::pair<int, int> &enemyCoordinates, const std::pair<int, int> &playerCoordinates) ;

    bool
    isPlayerVisible(const std::pair<int, int> &enemyCoordinate, const std::pair<int, int> &playerCoordinates, Map map);

    void moveEnemyTowardPlayer(const std::pair<int, int> &enemyCoordinate, const std::pair<int, int> &playerCoordinate);
};


#endif //GAME_ENEMY_H
