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
    void revive();
    int getPosX();
    int getPosY();
private:
    static const int ENEMY_WIDTH = 64;
    static const int ENEMY_HEIGHT = 64;
    static const int ENEMY_VEL = 2;
    static const int ENEMY_WALKING_1 = 0;
    static const int ENEMY_WALKING_2 = 1;
    static const int ENEMY_ATTACKING = 2;
    static const int ENEMY_DEAD = 3;
    bool isChasingPlayer;
    double previousAngle;
    int mPosX, mPosY;
    int destinationX, destinationY;
    SDL_Rect gSpriteClips[4];
    Timer shootDelayTimer;
    Timer animationTimer;
    Texture* texture;
    Path* path;
    Map* map;
    BloodEffectCollection* bloodEffectCollection;

    void moveEnemyOnPath(const std::pair<int, int> &enemyCoordinate);
    void setStripes();
    static bool
    playerIsCloseEnough(const std::pair<int, int> &enemyCoordinates, const std::pair<int, int> &playerCoordinates) ;
    void moveEnemyTowardPlayer(const std::pair<int, int> &enemyCoordinate, const std::pair<int, int> &playerCoordinate);

    double calculateTextureAngle();

    int getClipToRender();
};


#endif //GAME_ENEMY_H
