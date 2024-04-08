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
    std::vector<Tile> getTiles();
private:
    std::vector<int> tilesMap;
    std::vector<Tile> tiles;
    std::vector<Tile> visibleTiles;

};

#endif //GAME_MAP_H
