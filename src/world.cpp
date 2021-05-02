#include "world.hpp"
#include <iostream>

World::World(
        int width,
        int height,
        int tileArray[],
        std::unordered_map<int, std::string>* tileConverter
        ) :
    _width(width),
    _height(height),
    _tileArray(tileArray),
    _tileConverter(tileConverter)
{
}

int World::getWidth() const {
    return _width;
}

int World::getHeight() const {
    return _height;
}

int World::getTile(int x, int y) const {
    if (x >= _width or y >= _height) {
        return 0;
    }
    return _tileArray[x*_width+y];
}

std::string World::getTileRessource(int key) const {
    if (_tileConverter->count(key) == 0) {
        return std::string();
    }
    return _tileConverter->at(key);
}
