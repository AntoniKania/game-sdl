#include "tile.h"

void Tile::render(int x, int y, SDL_Rect* clip) {
    texture->render(x, y, clip);
}

TileType Tile::getType() {
    return type;
}

Tile::Tile(Texture* texture, TileType type, int x, int y) {
    this->texture = texture;
    this->type = type;
    this->x = x;
    this->y = y;
}

int Tile::getX() const {
    return this->x;
}

int Tile::getY() const {
    return this->y;
}

int Tile::getWidth() const {
    return texture->getWidth();
}

int Tile::getHeight() const {
    return texture->getHeight();
}

SDL_Rect Tile::getRect() const {
    return SDL_Rect{x, y, texture->getWidth(), texture->getHeight()};
}