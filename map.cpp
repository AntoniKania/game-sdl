#include <algorithm>
#include "map.h"
#include "camera.h"
#include "collision.h"

const int MAP_WIDTH = 30 * 2;
const int MAP_HEIGHT = 20 * 2;

Map::Map() {
    tilesMap = {
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,3,1,1,1,1,1,1,1,1,1,3,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,3,1,1,1,1,1,1,1,1,1,3,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,3,1,1,1,1,1,1,1,1,1,3,1,1,1,1,2,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,3,1,1,1,1,1,1,1,1,1,3,1,1,1,1,2,1,1,1,1,1,1,1,1,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,3,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,1,1,1,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,4,1,1,1,1,4,1,1,1,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,4,1,1,1,1,4,1,1,1,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,4,1,1,1,1,4,1,1,1,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,5,5,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,1,1,4,1,1,1,1,4,1,1,1,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,5,1,1,1,1,5,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,1,4,1,1,1,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,5,1,1,1,1,5,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,1,4,1,1,1,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,5,5,5,5,5,5,5,5,1,1,1,1,5,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,1,4,1,1,1,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,5,1,1,1,1,1,1,1,1,1,1,1,5,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,1,1,1,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,5,1,1,1,1,1,1,1,1,1,1,1,5,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,5,1,1,1,1,1,5,5,5,5,5,5,5,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,2,1,1,1,5,1,1,1,1,1,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };
}

void Map::load(Texture* groundTexture, Texture* treeTexture) {
    for (int i = 0; i <= MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int x = TILE_SIZE * j;
            int y = TILE_SIZE * i;
            int &tileType = tilesMap[MAP_WIDTH * i + j];
            if (tileType == 1) {
                Tile tile = Tile{groundTexture, GROUND, x, y};
                tiles.push_back(tile);
            } else if (tileType == 2) {
                Tile tile = Tile{treeTexture, WALL, x, y};
                tiles.push_back(tile);
            } else if (tileType == 3) {
                Tile tile = Tile{groundTexture, PATH_ENEMY_1, x, y};
                tiles.push_back(tile);
            } else if (tileType == 4) {
                Tile tile = Tile{groundTexture, PATH_ENEMY_2, x, y};
                tiles.push_back(tile);
            } else if (tileType == 5) {
                Tile tile = Tile{groundTexture, PATH_ENEMY_3, x, y};
                tiles.push_back(tile);
            }
        }
    }
}

void Map::draw(Camera* camera) {
    for (auto &tile : tiles) {
        if (Collision::AABB(tile.getRect(), camera->getRect())) {
            if (tile.getY() < MAP_HEIGHT * 32 / 2) {
                tile.render(tile.getX() - camera->x, tile.getY() - camera->y, nullptr, 180.0);
            } else {
                tile.render(tile.getX() - camera->x, tile.getY() - camera->y);
            }
        }
    }
}

Map::~Map() {
    if (!tilesMap.empty()) {
        //todo: destroy all textures??
        tilesMap = {};
    }
}

Tile Map::getTileAbove(const Tile& tile) {
    long tileIndex = distance(tiles.begin(), find(tiles.begin(), tiles.end(), tile));

    if (tileIndex - MAP_WIDTH < 0) {
        return tile;
    }

    return tiles.at(tileIndex - MAP_WIDTH);
}

Tile Map::getTileBelow(const Tile& tile) {
    long tileIndex = distance(tiles.begin(), find(tiles.begin(), tiles.end(), tile));
    if (tileIndex + MAP_WIDTH >= tiles.size()) {
        return tile;
    }

    return tiles.at(tileIndex + MAP_WIDTH);
}

Tile Map::getTileToRight(const Tile& tile) {
    long tileIndex = distance(tiles.begin(), find(tiles.begin(), tiles.end(), tile));
    if (tileIndex + 1 >= tiles.size()) {
        return tile;
    }

    return tiles.at(tileIndex + 1);
}

Tile Map::getTileToLeft(const Tile& tile) {
    long tileIndex = distance(tiles.begin(), find(tiles.begin(), tiles.end(), tile));
    if (tileIndex - 1 < 0) {
        return tile;
    }

    return tiles.at(tileIndex - 1);
}

std::vector<Tile> Map::getTiles() const {
    return tiles;
}

bool Map::isWallBetweenInStraightLine(const Vector2 &startPos, const Vector2 &endPos) {
    auto xStart = startPos.x;
    auto yStart = startPos.y;
    auto xEnd = endPos.x;
    auto yEnd = endPos.y;
    auto xDirection = xEnd - xStart;
    auto yDirection = yEnd - yStart;
    Tile currentTile = getTile(xStart, yStart);
    int tileWidth = currentTile.getWidth();
    int tileHeight = currentTile.getHeight();
    auto tForOneX = abs( (double) tileWidth / xDirection);
    auto tForOneY = abs((double) tileHeight / yDirection);
    auto tValue = 0.0;
    double tForNextBorderX;
    double tForNextBorderY;

    double distanceToFirstEdgeX;
    if (xDirection > 0) {
        distanceToFirstEdgeX = currentTile.getX() + tileWidth - xStart;
        tForNextBorderX = distanceToFirstEdgeX / tileWidth * tForOneX;
    } else {
        distanceToFirstEdgeX = xStart - currentTile.getX();
        tForNextBorderX = distanceToFirstEdgeX / tileWidth * tForOneX;
    }

    double distanceToFirstEdgeY;
    if (yDirection > 0) {
        distanceToFirstEdgeY = currentTile.getY() + tileHeight - yStart;
        tForNextBorderY = distanceToFirstEdgeY / tileHeight * tForOneY;
    } else {
        distanceToFirstEdgeY = yStart - currentTile.getY();
        tForNextBorderY = distanceToFirstEdgeY / tileHeight * tForOneY;
    }
    while (tValue < 1) {
        if (currentTile.getType() == TileType::WALL) {
            return true;
        }
        if (tForNextBorderX <= tForNextBorderY) {
            tValue = tForNextBorderX;
            tForNextBorderX += tForOneX;
            if (xDirection > 0) {
                currentTile = getTileToRight(currentTile);
            } else {
                currentTile = getTileToLeft(currentTile);
            }
        } else {
            tValue = tForNextBorderY;
            tForNextBorderY += tForOneY;
            if (yDirection > 0) {
                currentTile = getTileBelow(currentTile);
            } else {
                currentTile = getTileAbove(currentTile);
            }
        }
    }
    return false;
}

Tile Map::getTile(const int &posX, const int &posY) {
    int tileX = posX / TILE_SIZE;
    int tileY = posY / TILE_SIZE;

    int index = tileY * MAP_WIDTH + tileX;
    return tiles.at(index);
}
