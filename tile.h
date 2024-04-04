#ifndef GAME_TILE_H
#define GAME_TILE_H

#include "texture.h"

enum TileType {
    WALL,
    GROUND
};

class Tile {
public:
    explicit Tile(Texture* texture, TileType type, int x, int y);
    virtual ~Tile() = default;
    void render(int x, int y);
    TileType getType();
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
private:
    TileType type;
    Texture* texture;
    int x, y;
};


#endif //GAME_TILE_H
