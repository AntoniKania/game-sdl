#ifndef GAME_TILE_H
#define GAME_TILE_H

#include <SDL2/SDL.h>
#include "texture.h"

enum TileType {
    WALL,
    GROUND,
    PATH_ENEMY_1,
    PATH_ENEMY_2,
    PATH_ENEMY_3,
    PATH_ENEMY_4,
    PATH_ENEMY_5,
    PATH_ENEMY_6,
    PATH_ENEMY_7
};

class Tile {
public:
    explicit Tile(Texture* texture, TileType type, int x, int y);
    virtual ~Tile() = default;
    void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0f);
    TileType getType();
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    SDL_Rect getRect() const;
    bool operator==(const Tile&) const;
    bool operator!=(const Tile&) const;
    void changeColor();
private:
    TileType type;
    Texture* texture;
    int x, y;
    bool colorChanged;
};


#endif //GAME_TILE_H
