#include "world.hpp"
#include <iostream>

World::World(
        unsigned int width,
        unsigned int height,
        std::unique_ptr<Tile[]>& tiles
        ) :
    _width(width),
    _height(height),
    _tiles(std::move(tiles))
{
}

unsigned int World::getWidth() const
{
    return _width;
}

unsigned int World::getHeight() const
{
    return _height;
}

void World::draw(sf::RenderWindow& window)
{
    float i = 0;
    for (float x = 0 ; x < _width ; x++ )
    {
        for (float y = 0 ; y < _height ; y++, i++)
        {
            _tiles[i].draw(window);
        }
    }
}
