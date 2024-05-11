#include "enemy.h"

Enemy::Enemy(Texture *texture, Map *map, Path *path, BloodEffectCollection *bloodEffectCollection) {
    this->texture = texture;
    this->path = path;
    Tile &tile = path->getPathNode()->tile;
    this->mPosX = tile.getX() + tile.getWidth() / 2 - texture->getWidth() / 2;
    this->mPosY = tile.getY() + tile.getHeight() / 2 - texture->getHeight() / 2;
    this->isAlive = true;
    this->map = map;
    this->bloodEffectCollection = bloodEffectCollection;
}

void Enemy::move(const Player &dot) {
    if (!this->isAlive) {
        return;
    }
    auto enemyCoordinates = std::make_pair(mPosX + texture->getWidth() / 2,
                                          mPosY + texture->getHeight() / 2);
    auto playerCoordinates = std::make_pair(dot.getPosX() + dot.DOT_WIDTH / 2,
                                            dot.getPosY() + dot.DOT_HEIGHT / 2);

    if (playerIsCloseEnough(enemyCoordinates, playerCoordinates) ||
            map->isWallBetweenInStraightLine(Vector2(playerCoordinates.first, playerCoordinates.second),
                                                   Vector2(enemyCoordinates.first, enemyCoordinates.second))
        ) {
        moveEnemyTowardPlayer(enemyCoordinates, playerCoordinates);
    } else {
        moveEnemyOnPath(enemyCoordinates);
    }
}

bool Enemy::playerIsCloseEnough(const std::pair<int, int> &enemyCoordinates,
                                const std::pair<int, int> &playerCoordinates) {
    return abs(enemyCoordinates.first - playerCoordinates.first) < 500 &&
           abs(enemyCoordinates.second - playerCoordinates.second) < 500;
}

void Enemy::moveEnemyOnPath(const std::pair<int, int> &enemyCoordinate) {
    Tile &tile = path->getPathNode()->tile;
    auto pathCoordinate = std::make_pair(tile.getX() + tile.getWidth() / 2,
                                         tile.getY() + tile.getHeight() / 2);
    if (pathCoordinate == enemyCoordinate) {
        path->incrementPathNode();
    }
    int pathX = pathCoordinate.first;
    int enemyX = enemyCoordinate.first;
    if (pathX < enemyX) {
        mPosX -= ENEMY_VEL;
    } else if (pathX > enemyX) {
        mPosX += ENEMY_VEL;
    }
    int pathY = pathCoordinate.second;
    int enemyY = enemyCoordinate.second;
    if (pathY < enemyY) {
        mPosY -= ENEMY_VEL;
    } else if (pathY > enemyY) {
        mPosY += ENEMY_VEL;
    }
}

void Enemy::moveEnemyTowardPlayer(const std::pair<int, int> &enemyCoordinate, const std::pair<int, int> &playerCoordinate) {
    int enemyX = enemyCoordinate.first;
    int playerX = playerCoordinate.first;
    if (playerX < enemyX) {
        mPosX -= ENEMY_VEL;
    } else if (playerX > enemyX) {
        mPosX += ENEMY_VEL;
    }
    int playerY = playerCoordinate.second;
    int enemyY = enemyCoordinate.second;
    if (playerY < enemyY) {
        mPosY -= ENEMY_VEL;
    } else if (playerY > enemyY) {
        mPosY += ENEMY_VEL;
    }
}

void Enemy::render(int camX, int camY) {
    texture->render(mPosX - camX, mPosY - camY);
}

void Enemy::kill() {
    this->isAlive = false;
    bloodEffectCollection->createBloodEffect(mPosX, mPosY);
}

int Enemy::getPosY() {
    return this->mPosY;
}

int Enemy::getPosX() {
    return this->mPosX;
}
