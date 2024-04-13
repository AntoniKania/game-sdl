#include "enemy.h"

Enemy::Enemy(Texture *texture, Path *path) {
    this->texture = texture;
    this->path = path;
    Tile &tile = path->getPathNode()->tile;
    this->mPosX = tile.getX() + tile.getWidth() / 2 - texture->getWidth() / 2;
    this->mPosY = tile.getY() + tile.getHeight() / 2 - texture->getHeight() / 2;
}

void Enemy::move() {
    auto enemyCoordinate = std::make_pair(mPosX + texture->getWidth() / 2,
                                          mPosY + texture->getHeight() / 2);
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

void Enemy::render(int camX, int camY) {
    texture->render(mPosX - camX, mPosY - camY);
}