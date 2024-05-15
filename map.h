#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include "tile.h"
#include "camera.h"
#include "vector2.h"

class Map {
public:
    Map();
    ~Map();

    void draw(Camera* camera);
    void load(Texture* groundTexture, Texture* treeTexture);
    std::vector<Tile> getTiles() const;
    Tile getTileAbove(const Tile& tile);
    Tile getTileBelow(const Tile& tile);
    Tile getTileToRight(const Tile& tile);
    Tile getTileToLeft(const Tile& tile);
    std::vector<Tile> tiles;
    bool isWallBetweenInStraightLine(const Vector2& startPos, const Vector2& endPos);
    Tile getTile(const int& posX, const int& posY);
    static const int TILE_SIZE = 64;
private:
    std::vector<int> tilesMap;
    std::vector<Tile> visibleTiles;
};

#endif //GAME_MAP_H
