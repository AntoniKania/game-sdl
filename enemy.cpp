#include "enemy.h"

Enemy::Enemy(Texture *texture, Path *path) {
    this->texture = texture;
    this->path = path;
    Tile &tile = path->getPathNode()->tile;
    this->mPosX = tile.getX() + tile.getWidth() / 2 - texture->getWidth() / 2;
    this->mPosY = tile.getY() + tile.getHeight() / 2 - texture->getHeight() / 2;
}

void Enemy::move(const Dot &dot, const Map &map) {
    auto enemyCoordinates = std::make_pair(mPosX + texture->getWidth() / 2,
                                          mPosY + texture->getHeight() / 2);
    auto playerCoordinates = std::make_pair(dot.getPosX() + dot.DOT_WIDTH / 2,
                                            dot.getPosY() + dot.DOT_HEIGHT / 2);

    moveEnemyOnPath(enemyCoordinates);
    playerIsVisible(enemyCoordinates, playerCoordinates, map);
//    if (playerIsCloseEnough(enemyCoordinates, playerCoordinates) &&
//        playerIsVisible(enemyCoordinates, playerCoordinates, map)) {
//
//    } else {
//        moveEnemyOnPath(enemyCoordinates);
//    }
}

bool Enemy::playerIsCloseEnough(const std::pair<int, int> &enemyCoordinates,
                                const std::pair<int, int> &playerCoordinates) {
    return abs(enemyCoordinates.first - playerCoordinates.first) < 300 &&
           abs(enemyCoordinates.second - playerCoordinates.second) < 300;
}

bool Enemy::playerIsVisible(const std::pair<int, int> &enemyCoordinate,
                                const std::pair<int, int> &playerCoordinates,
                                Map map) {
    auto xStart = enemyCoordinate.first;
    auto yStart = enemyCoordinate.second;
    auto xEnd = playerCoordinates.first;
    auto yEnd = playerCoordinates.second;
    auto xDirection = xEnd - xStart;
    auto yDirection = yEnd - yStart;
    Tile currentTile = path->getPathNode()->tile;
    int tileWidth = currentTile.getWidth();
    int tileHeight = currentTile.getHeight();
    auto tForOneX = abs( (double) tileWidth / xDirection);
    auto tForOneY = abs((double) tileHeight / yDirection);
    auto tValue = 0.0;
    double tForNextBorderX;
    double tForNextBorderY;

    double distanceToFirstEdgeX;
    // currentTile is based on current PathNode->tile, but in fact the enemy can still be in previous tile.
    if (xStart < currentTile.getX()) {
        currentTile = map.getTileToLeft(currentTile);
    } else if (xStart > currentTile.getX() + tileWidth) {
        currentTile = map.getTileToRight(currentTile);
    }
    if (xDirection > 0) {
        distanceToFirstEdgeX = currentTile.getX() + tileWidth - xStart;
        tForNextBorderX = distanceToFirstEdgeX / tileWidth * tForOneX;
    } else {
        distanceToFirstEdgeX = xStart - currentTile.getX();
        tForNextBorderX = distanceToFirstEdgeX / tileWidth * tForOneX;
    }

    double distanceToFirstEdgeY;
    if (yStart < currentTile.getY()) {
        currentTile = map.getTileAbove(currentTile);
    } else if (yStart > currentTile.getY() + tileHeight) {
        currentTile = map.getTileBelow(currentTile);
    }
    if (yDirection > 0) {
        distanceToFirstEdgeY = currentTile.getY() + tileHeight - yStart;
        tForNextBorderY = distanceToFirstEdgeY / tileHeight * tForOneY;
    } else {
        distanceToFirstEdgeY = yStart - currentTile.getY();
        tForNextBorderY = distanceToFirstEdgeY / tileHeight * tForOneY;
    }
    while (tValue < 1) {
        if (currentTile.getType() == TileType::WALL) {
            printf("Player not visible\n");
            return false;
        }
        if (tForNextBorderX <= tForNextBorderY) {
            tValue = tForNextBorderX;
            tForNextBorderX += tForOneX;
            if (xDirection > 0) {
                currentTile = map.getTileToRight(currentTile);
            } else {
                currentTile = map.getTileToLeft(currentTile);
            }
        } else {
            tValue = tForNextBorderY;
            tForNextBorderY += tForOneY;
            if (yDirection > 0) {
                currentTile = map.getTileBelow(currentTile);
            } else {
                currentTile = map.getTileAbove(currentTile);
            }
        }
    }
    printf("Player visible!!!!!!!!!!!!!!\n");
    return true;
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

void Enemy::render(int camX, int camY) {
    texture->render(mPosX - camX, mPosY - camY);
}
