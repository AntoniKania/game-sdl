#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include "tile.h"
#include "camera.h"

class Map {
public:
    Map();
    ~Map();

    void draw(Camera* camera);
    void load(Texture* grayTexture, Texture* redTexture);
    std::vector<Tile> getTiles() const;
    Tile getTileAbove(const Tile& tile);
    Tile getTileBelow(const Tile& tile);
    Tile getTileToRight(const Tile& tile);
    Tile getTileToLeft(const Tile& tile);
    std::vector<Tile> tiles;
private:
    std::vector<int> tilesMap;
    std::vector<Tile> visibleTiles;

};

#endif //GAME_MAP_H
