#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include "tile.h"

class Map {
public:
    Map();
    ~Map();

    void draw();
    void load(Texture* grayTexture, Texture* redTexture);
    std::vector<Tile> getTiles();
private:
    std::vector<int> tilesMap;
    std::vector<Tile> tiles;
};

#endif //GAME_MAP_H
