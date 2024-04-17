#include "dot.h"
#include "collision.h"

Dot::Dot() {
    mPosX = 0;
    mPosY = 0;

    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move(const std::vector<Tile>& tiles, const int& screenWidth, const int& screenHeight) {
    mPosX += mVelX;

    if ((mPosX < 0) || (mPosX + DOT_WIDTH > screenWidth || isColliding(tiles))) {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > screenHeight || isColliding(tiles))) {
        mPosY -= mVelY;
    }
}

bool Dot::isColliding(const std::vector<Tile>& tiles) {
    auto dotRect = SDL_Rect {mPosX, mPosY, DOT_WIDTH, DOT_HEIGHT};
    for (auto tile : tiles) {
        auto tileRectangle = SDL_Rect{tile.getX(), tile.getY(), tile.getWidth(), tile.getHeight()};
        if (tile.getType() == WALL && Collision::AABB(tileRectangle, dotRect)) {
            return true;
        }
    }
    return false;
}

void Dot::render(int camX, int camY) {
    texture->render(mPosX - camX, mPosY - camY);
}

int Dot::getPosX() const {
    return mPosX;
}

int Dot::getPosY() const {
    return mPosY;
}

Dot::Dot(Texture *texture) {
    this->texture = texture;
    mPosX = 0;
    mPosY = 0;

    mVelX = 0;
    mVelY = 0;
}