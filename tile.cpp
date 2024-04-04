#include "tile.h"

void Tile::render(int x, int y) {
    texture->render(x, y);
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