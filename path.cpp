#include "path.h"

Path::Path(const Map &map, TileType tileType) {
    this->map = map;
    this->pathTileType = tileType;
    loadPath();
}

void Path::loadPath() {
    PathNode* firstNode = nullptr;
    PathNode* previousNode = nullptr;
    PathNode* currentNode = nullptr;

    bool firstPathNodeFound = false;
    while (!firstPathNodeFound) {
        for (auto tile : map.tiles) {
            if (tile.getType() == pathTileType) {
                auto* newNode = new PathNode{tile, nullptr};
                firstNode = newNode;
                currentNode = firstNode;
                firstPathNodeFound = true;
                break;
            }
        }
    }

    bool pathCreated = false;
    while (!pathCreated) {
        Tile &currentTile = currentNode->tile;
        auto previousTile = previousNode == nullptr ? currentTile : previousNode->tile;
        Tile nextPathTail = getNextPathTail(currentTile, previousTile);
        if (nextPathTail == currentTile) {
            nextPathTail = getNextPathTail(currentTile, currentTile);
        }
        if (nextPathTail == firstNode->tile) {
            currentNode->next = firstNode;
            pathCreated = true;
            continue;
        }
        auto* nextNode = new PathNode{nextPathTail, nullptr};
        previousNode = currentNode;
        currentNode->next = nextNode;
        currentNode = nextNode;
    }

    currentPathNode = firstNode;
}

Tile Path::getNextPathTail(const Tile& tile, const Tile& previousTile) {
    Tile tileAbove = map.getTileAbove(tile);
    Tile tileToRight = map.getTileToRight(tile);
    Tile tileBelow = map.getTileBelow(tile);
    Tile tileToLeft = map.getTileToLeft(tile);
    if (tileAbove != tile && tileAbove.getType() == pathTileType && tileAbove != previousTile) {
        return tileAbove;
    } else if (tileToRight != tile && tileToRight.getType() == pathTileType && tileToRight != previousTile) {
        return tileToRight;
    } else if (tileBelow != tile && tileBelow.getType() == pathTileType && tileBelow != previousTile) {
        return tileBelow;
    } else if (tileToLeft != tile && tileToLeft.getType() == pathTileType && tileToLeft != previousTile) {
        return tileToLeft;
    } else {
        return tile;
    }
}

Path::PathNode* Path::getPathNode() {
    return currentPathNode;
}

void Path::incrementPathNode() {
    currentPathNode = currentPathNode->next;
}
