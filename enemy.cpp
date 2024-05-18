#include "enemy.h"

Enemy::Enemy(Texture *texture, Map *map, Path *path, BloodEffectCollection *bloodEffectCollection) {
    this->texture = texture;
    this->path = path;
    Tile &tile = path->getPathNode()->tile;
    this->mPosX = tile.getX();
    this->mPosY = tile.getY();
    this->isAlive = true;
    this->map = map;
    this->bloodEffectCollection = bloodEffectCollection;
    this->shootDelayTimer = Timer();
    this->animationTimer = Timer();
    this->isChasingPlayer = false;

    setStripes();
}

void Enemy::move(const Player &player) {
    if (!this->isAlive || player.gotKilled()) {
        return;
    }
    auto enemyCoordinates = std::make_pair(mPosX + ENEMY_WIDTH / 2,
                                          mPosY + texture->getHeight() / 2);
    auto playerCoordinates = std::make_pair(player.getPosX() + player.WIDTH / 2,
                                            player.getPosY() + player.HEIGHT / 2);

    if (playerIsCloseEnough(enemyCoordinates, playerCoordinates) &&
            !map->isWallBetweenInStraightLine(Vector2(playerCoordinates.first, playerCoordinates.second),
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

    destinationX = pathX;
    destinationY = pathY;
    isChasingPlayer = false;
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

    destinationX = playerX;
    destinationY = playerY;
    isChasingPlayer = true;
}

void Enemy::revive() {
    isAlive = true;
    isChasingPlayer = false;
    mPosX = path->getPathNode()->tile.getX();
    mPosY = path->getPathNode()->tile.getY();
}

void Enemy::render(int camX, int camY) {
    int clipToRender = getClipToRender();
    SDL_Rect* currentClip = &gSpriteClips[ clipToRender ];
    texture->render(mPosX - camX, mPosY - camY, currentClip, calculateTextureAngle());
}

int Enemy::getPosY() {
    return this->mPosY;
}

int Enemy::getPosX() {
    return this->mPosX;
}

void Enemy::kill(int shooterPosX, int shooterPoxY) {
    this->isAlive = false;
    bloodEffectCollection->createBloodEffects(shooterPosX, shooterPoxY, mPosX, mPosY);
}

bool Enemy::canShootPlayer(const Player &player) {
    if (!player.isAlive || !isAlive) {
        return false;
    }
    shootDelayTimer.start();
    auto enemyCoordinates = std::make_pair(mPosX + ENEMY_WIDTH / 2,
                                           mPosY + texture->getHeight() / 2);
    auto playerCoordinates = std::make_pair(player.getPosX() + player.WIDTH / 2,
                                            player.getPosY() + player.HEIGHT / 2);

    if (!playerIsCloseEnough(enemyCoordinates, playerCoordinates) || map->isWallBetweenInStraightLine(
            Vector2(playerCoordinates.first, playerCoordinates.second),
            Vector2(enemyCoordinates.first, enemyCoordinates.second))) {
        shootDelayTimer.stop();
        return false;
    }

    if (shootDelayTimer.getTicks() / 1000.0f > 1.7) {
        shootDelayTimer.stop();
        return true;
    } else {
        return false;
    }
}

void Enemy::setStripes() {
    gSpriteClips[ 0 ].x =   0;
    gSpriteClips[ 0 ].y =   0;
    gSpriteClips[ 0 ].w = ENEMY_WIDTH;
    gSpriteClips[ 0 ].h = ENEMY_HEIGHT;

    gSpriteClips[ 1 ].x =  64;
    gSpriteClips[ 1 ].y =   0;
    gSpriteClips[ 1 ].w = ENEMY_WIDTH;
    gSpriteClips[ 1 ].h = ENEMY_HEIGHT;

    gSpriteClips[ 2 ].x = 192;
    gSpriteClips[ 2 ].y =   0;
    gSpriteClips[ 2 ].w = ENEMY_WIDTH;
    gSpriteClips[ 2 ].h = ENEMY_HEIGHT;

    gSpriteClips[ 3 ].x = 256;
    gSpriteClips[ 3 ].y =   0;
    gSpriteClips[ 3 ].w = ENEMY_WIDTH;
    gSpriteClips[ 3 ].h = ENEMY_HEIGHT;
}

double Enemy::calculateTextureAngle() {
    if (!isAlive) {
        return previousAngle;
    }
    int dx = destinationX - mPosX - ENEMY_WIDTH / 2;
    int dy = destinationY - mPosY - texture->getHeight() / 2;

    if (dx == 0 && dy == 0) {
        return previousAngle;
    }

    double angleRadians = atan2(dy, dx);
    double angleDegrees = angleRadians * (180.0 / M_PI);

    angleDegrees += 180.0;

    while (angleDegrees < 0) {
        angleDegrees += 360.0;
    }
    while (angleDegrees >= 360.0) {
        angleDegrees -= 360.0;
    }

    previousAngle = angleDegrees;
    return angleDegrees;
}

int Enemy::getClipToRender() {
    if (!isAlive) {
        return ENEMY_DEAD;
    } else if (isChasingPlayer) {
        return ENEMY_ATTACKING;
    }
    if (animationTimer.getTicks() / 1000.0f > 1.5) {
        animationTimer.stop();
    }
    animationTimer.start();
    if (animationTimer.getTicks() / 1000.0f < 0.75) {
        return ENEMY_WALKING_1;
    } else {
        return ENEMY_WALKING_2;
    }
}