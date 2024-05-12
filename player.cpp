#include "player.h"
#include "collision.h"

void Player::handleEvent(SDL_Event& e) {
    if (!isAlive) {
        return;
    }
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_w: mVelY -= DOT_VEL; break;
            case SDLK_s: mVelY += DOT_VEL; break;
            case SDLK_a: mVelX -= DOT_VEL; break;
            case SDLK_d: mVelX += DOT_VEL; break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch(e.key.keysym.sym)
        {
            case SDLK_w: mVelY += DOT_VEL; break;
            case SDLK_s: mVelY -= DOT_VEL; break;
            case SDLK_a: mVelX += DOT_VEL; break;
            case SDLK_d: mVelX -= DOT_VEL; break;
        }
    }
}

void Player::move(const std::vector<Tile>& tiles, const int& screenWidth, const int& screenHeight) {
    mPosX += mVelX;

    if ((mPosX < 0) || (mPosX + DOT_WIDTH > screenWidth || isColliding(tiles))) {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > screenHeight || isColliding(tiles))) {
        mPosY -= mVelY;
    }
}

bool Player::isColliding(const std::vector<Tile>& tiles) {
    auto dotRect = SDL_Rect {mPosX, mPosY, DOT_WIDTH, DOT_HEIGHT};
    for (auto tile : tiles) {
        auto tileRectangle = SDL_Rect{tile.getX(), tile.getY(), tile.getWidth(), tile.getHeight()};
        if (tile.getType() == WALL && Collision::AABB(tileRectangle, dotRect)) {
            return true;
        }
    }
    return false;
}

void Player::render(int camX, int camY) {
    texture->render(mPosX - camX, mPosY - camY);
}

int Player::getPosX() const {
    return mPosX;
}

int Player::getPosY() const {
    return mPosY;
}

Player::Player(Texture *texture) {
    this->texture = texture;
    mPosX = 0;
    mPosY = 0;

    mVelX = 0;
    mVelY = 0;
    isAlive = true;
}

void Player::kill(BloodEffectCollection *bloodEffectCollection, int shooterPosX, int shooterPosY) {
    mVelX = 0;
    mVelY = 0;
    isAlive = false;
    bloodEffectCollection->createBloodEffects(shooterPosX, shooterPosY, mPosX, mPosY);
}
