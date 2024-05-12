#include "shotgun.h"

Shotgun::Shotgun(std::vector<Enemy *> *enemies, Player *player, const Map &map, Camera *camera) {
    this->camera = camera;
    this->map = map;
    this->enemies = enemies;
    this->player = player;
    this->spreadAngle = 30;
}

bool Shotgun::canKillEnemy(Enemy* enemy) {
    Vector2 playerPos = Vector2(player->getPosX(), player->getPosY());
    Vector2 enemyPos = Vector2(enemy->getPosX(), enemy->getPosY());
    return map.isWallBetweenInStraightLine(playerPos, enemyPos) &&
            isEnemyCloseEnough(enemy) &&
            isEnemyWithinSpreadAngle(enemy);
}

void Shotgun::handleEvent(SDL_Event &e) {
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT
    ) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        Vector2 playerPos = Vector2(player->getPosX(), player->getPosY());
        Vector2 destination = Vector2(mouseX + camera->x, mouseY + camera->y);
        fire(playerPos, destination);
    }
}

void Shotgun::fire(const Vector2 &ptStart, const Vector2 &ptTarget) {
    shooterPos = ptStart;
    targetPos = ptTarget;
    targetAngle = calculateAngle(shooterPos.x, shooterPos.y, targetPos.x, targetPos.y);
    float spreadAngleRadians = spreadAngle * (M_PI / 180.0);
    minAngle = targetAngle - spreadAngleRadians / 2.0f;
    maxAngle = targetAngle + spreadAngleRadians / 2.0f;

    if (minAngle < -M_PI) {
        minAngle += 2 * M_PI;
    }
    if (minAngle > M_PI) {
        minAngle -= 2 * M_PI;
    }
    if (maxAngle < -M_PI) {
        maxAngle += 2 * M_PI;
    }
    if (maxAngle > M_PI) {
        maxAngle -= 2 * M_PI;
    }

    m_ptVelocity = ptTarget - ptStart;

    for (auto enemy : *enemies) {
        if (canKillEnemy(enemy) && enemy->isAlive) {
            printf("Enemy killed!");
            enemy->kill(shooterPos.x, shooterPos.y);
        }
    }
//    removeKilledEnemies();
}

void Shotgun::removeKilledEnemies() {
    for (int i = 0; i < enemies->size(); i++) {
        if (!enemies->at(i)->isAlive) {
            enemies->erase(enemies->begin() + i);
            i--;
        }
    }
}

float Shotgun::calculateAngle(float shooterPosX, float shooterPosY, float targetPosX, float targetPosY) {
    float deltaX = targetPosX - shooterPosX;
    float deltaY = targetPosY - shooterPosY;
    return atan2(deltaY, deltaX);
}

bool Shotgun::isEnemyWithinSpreadAngle(Enemy *enemy) {
    auto angleToEnemy = calculateAngle(shooterPos.x, shooterPos.y,
                                       enemy->getPosX(), enemy->getPosY());
    while (angleToEnemy > M_PI) {
        angleToEnemy -= 2 * M_PI;
    }
    while (angleToEnemy < -M_PI) {
        angleToEnemy += 2 * M_PI;
    }

    return (minAngle <= maxAngle) ? (angleToEnemy >= minAngle && angleToEnemy <= maxAngle) :
                          (angleToEnemy >= minAngle || angleToEnemy <= maxAngle);

}

float Shotgun::calculateDistance(const Vector2& pos1, const Vector2& pos2) {
    float deltaX = pos2.x - pos1.x;
    float deltaY = pos2.y - pos1.y;
    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

bool Shotgun::isEnemyCloseEnough(Enemy *enemy) {
    Vector2 enemyPos = Vector2(enemy->getPosX(), enemy->getPosY());
    float distance = calculateDistance(shooterPos, enemyPos);
    bool closeEnough = distance <= SHOOTING_DISTANCE;
    if (closeEnough) {
        printf("Enemy close enough!\n Distance: %f\n", distance);
    } else {
        printf("Enemy not close enough!\n Distance: %f\n", distance);
    }
    return closeEnough;
}
