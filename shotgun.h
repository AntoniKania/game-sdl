#ifndef GAME_SHOTGUN_H
#define GAME_SHOTGUN_H

#include <vector>
#include "vector2.h"
#include "player.h"
#include "enemy.h"

class Shotgun {
public:
    Vector2 shooterPos;
    Vector2 targetPos;
    Vector2 m_ptVelocity;
    const int SHOOTING_DISTANCE = 250;
    Shotgun(Texture* texture, std::vector<Enemy*>* enemies, Player* player, const Map& map, Camera* camera);
    void handleEvent(SDL_Event& e);
    void fire(const Vector2 &ptStart, const Vector2 &ptTarget);
    void render(int camX, int camY);
private:
    Camera* camera;
    Texture* texture;
    Timer afterShotTimer;
    Map map;
    float spreadAngle;
    float targetAngle;
    float minAngle;
    float maxAngle;
    std::vector<Enemy*>* enemies;
    Player* player;
    bool canKillEnemy(Enemy* enemy);
    bool isEnemyCloseEnough(Enemy* enemy);
    bool isEnemyWithinSpreadAngle(Enemy* enemy);
    float calculateAngle(float shooterPosX, float shooterPosY, float targetPosX, float targetPosY);
    static float calculateDistance(const Vector2& pos1, const Vector2& pos2);
    double calculateTextureAngle();
};


#endif //GAME_SHOTGUN_H
