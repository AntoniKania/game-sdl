#ifndef GAME_PATH_H
#define GAME_PATH_H

#include "map.h"

class Path {
public:
    explicit Path(const Map& map);
    struct PathNode {
        Tile tile;
        PathNode* next;
    };
    PathNode* getPathNode();
    void incrementPathNode();
private:
    void loadPath();
    PathNode* currentPathNode;
    Map map;

    Tile getNextPathTail(const Tile& tile, const Tile& previousTile);
};


#endif //GAME_PATH_H
