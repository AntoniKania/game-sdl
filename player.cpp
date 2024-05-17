#include "player.h"
#include "collision.h"

void Player::handleEvent(SDL_Event& e) {
    if (!isAlive) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            if (e.key.keysym.sym == SDLK_SPACE) {
                revive();
            }
        }
    } else {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            switch(e.key.keysym.sym) {
                case SDLK_w: mVelY -= DOT_VEL; break;
                case SDLK_s: mVelY += DOT_VEL; break;
                case SDLK_a: mVelX -= DOT_VEL; break;
                case SDLK_d: mVelX += DOT_VEL; break;
            }
        } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            switch(e.key.keysym.sym)
            {
                case SDLK_w: mVelY += DOT_VEL; break;
                case SDLK_s: mVelY -= DOT_VEL; break;
                case SDLK_a: mVelX += DOT_VEL; break;
                case SDLK_d: mVelX -= DOT_VEL; break;
            }
        }
    }
}

void Player::revive() {
    isAlive = true;
    mPosX = START_POS_X;
    mPosY = START_POS_Y;
}

void Player::move(const std::vector<Tile>& tiles, const int& screenWidth, const int& screenHeight) {
    mPosX += mVelX;

    if ((mPosX < 0) || (mPosX + WIDTH > screenWidth || isColliding(tiles))) {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if ((mPosY < 0) || (mPosY + HEIGHT > screenHeight || isColliding(tiles))) {
        mPosY -= mVelY;
    }
}

bool Player::isColliding(const std::vector<Tile>& tiles) {
    auto dotRect = SDL_Rect {mPosX, mPosY, WIDTH, HEIGHT};
    for (auto tile : tiles) {
        auto tileRectangle = SDL_Rect{tile.getX(), tile.getY(), tile.getWidth(), tile.getHeight()};
        if (tile.getType() == WALL && Collision::AABB(tileRectangle, dotRect)) {
            return true;
        }
    }
    return false;
}

void Player::render(int camX, int camY) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    texture->render(mPosX - camX, mPosY - camY, nullptr, calculateAngle(mouseX + camX, mouseY + camY));
}

double Player::calculateAngle(int mousePosX, int mousePosY) {
    if (!isAlive) {
        return previousAngle;
    }
    int dx = mousePosX - mPosX;
    int dy = mousePosY - mPosY;

    double angleRadians = atan2(dy, dx);
    double angleDegrees = angleRadians * (180.0 / M_PI);

    while (angleDegrees < 0) {
        angleDegrees += 360.0;
    }
    while (angleDegrees >= 360.0) {
        angleDegrees -= 360.0;
    }

    previousAngle = angleDegrees;
    return angleDegrees;
}

int Player::getPosX() const {
    return mPosX;
}

int Player::getPosY() const {
    return mPosY;
}

Player::Player(Texture *texture) {
    this->texture = texture;
    mPosX = START_POS_X;
    mPosY = START_POS_Y;

    mVelX = 0;
    mVelY = 0;
    isAlive = false;
}

void Player::kill(BloodEffectCollection *bloodEffectCollection, int shooterPosX, int shooterPosY) {
    mVelX = 0;
    mVelY = 0;
    isAlive = false;
    bloodEffectCollection->createBloodEffects(shooterPosX, shooterPosY, mPosX, mPosY);
}

void Player::kill() {
    mVelX = 0;
    mVelY = 0;
    isAlive = false;
}
