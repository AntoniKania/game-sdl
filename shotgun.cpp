#include "shotgun.h"

Shotgun::Shotgun(Texture* texture, std::vector<Enemy *> *enemies, Player *player, const Map &map, Camera *camera) {
    this->texture = texture;
    this->camera = camera;
    this->map = map;
    this->enemies = enemies;
    this->player = player;
    this->spreadAngle = 30;
    this->afterShotTimer = Timer();
}

bool Shotgun::canKillEnemy(Enemy* enemy) {
    Vector2 playerPos = Vector2(player->getPosX(), player->getPosY());
    Vector2 enemyPos = Vector2(enemy->getPosX(), enemy->getPosY());
    return !map.isWallBetweenInStraightLine(playerPos, enemyPos) &&
            isEnemyCloseEnough(enemy) &&
            isEnemyWithinSpreadAngle(enemy);
}

void Shotgun::handleEvent(SDL_Event &e) {
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT
    ) {
        if (!player->isAlive) {
            return;
        }
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

    afterShotTimer.stop();
    afterShotTimer.start();

    for (auto enemy : *enemies) {
        if (canKillEnemy(enemy) && enemy->isAlive) {
            enemy->kill(shooterPos.x, shooterPos.y);
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
    return distance <= SHOOTING_DISTANCE;
}

void Shotgun::render(int camX, int camY) {
    if (afterShotTimer.getTicks() / 1000.0f == 0 || afterShotTimer.getTicks() / 1000.0f > 0.05) {
        return;
    } else {
        auto point = SDL_Point{0, 64};
        texture->render(player->getPosX() + player->WIDTH / 2 - camX, player->getPosY() + player->HEIGHT / 2 - camY - 64,
                        nullptr, calculateTextureAngle(), &point);
    }
}

void Shotgun::renderEnemyShooting(int camX, int camY, Enemy *enemy) {
    if (enemy != enemyThatShotPlayer) {
        return;
    }
    if (afterShotTimerForEnemy.getTicks() / 1000.0f > 0.1) {
        afterShotTimerForEnemy.stop();
        enemyThatShotPlayer = nullptr;
        return;
    } else {
        auto point = SDL_Point{0, 64};
        texture->render(enemy->getPosX() + player->WIDTH / 2 - camX, enemy->getPosY() + player->HEIGHT / 2 - camY - 64,
                        nullptr, calculateTextureAngle(), &point, SDL_RendererFlip::SDL_FLIP_VERTICAL);
    }
}

void Shotgun::markEnemyThatShotPlayer(Enemy *enemy) {
    enemyThatShotPlayer = enemy;
    shooterPos = Vector2(enemy->getPosX(), enemy->getPosY());
    targetPos = Vector2(player->getPosX() + player->HEIGHT / 2, player->getPosY() + player->WIDTH / 2);
    afterShotTimerForEnemy.start();
}

double Shotgun::calculateTextureAngle() {
    int dx = targetPos.x - shooterPos.x - map.TILE_SIZE / 2;
    int dy = targetPos.y - shooterPos.y - map.TILE_SIZE / 2;

    double angleRadians = atan2(dy, dx);
    double angleDegrees = angleRadians * (180.0 / M_PI);

    while (angleDegrees < 0) {
        angleDegrees += 360.0;
    }
    while (angleDegrees >= 360.0) {
        angleDegrees -= 360.0;
    }

    return angleDegrees;
}
