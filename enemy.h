#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H


#include "texture.h"
#include "player.h"
#include "map.h"
#include "path.h"
#include "vector2.h"
#include "blood_effect.h"
#include "timer.h"

class Enemy {
public:
    bool isAlive;
    Enemy(Texture* texture, Map *map, Path *path, BloodEffectCollection *bloodEffectCollection);
    void render(int camX, int camY);
    bool canShootPlayer(const Player &player);
    void move(const Player &player);
    void kill(int shooterPosX, int shooterPoxY);
    int getPosX();
    int getPosY();
private:
    static const int ENEMY_VEL = 2;
    int mPosX, mPosY;
    Timer timer;
    Texture* texture;
    Path* path;
    Map* map;
    BloodEffectCollection* bloodEffectCollection;

    void moveEnemyOnPath(const std::pair<int, int> &enemyCoordinate);

    static bool
    playerIsCloseEnough(const std::pair<int, int> &enemyCoordinates, const std::pair<int, int> &playerCoordinates) ;

    void moveEnemyTowardPlayer(const std::pair<int, int> &enemyCoordinate, const std::pair<int, int> &playerCoordinate);
};


#endif //GAME_ENEMY_H
