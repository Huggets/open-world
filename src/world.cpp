#include "world.hpp"
#include <iostream>

World::World(
        unsigned int width,
        unsigned int height,
        std::unique_ptr<std::vector<std::vector<Tile>>>& tiles
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
    for (float x = 0 ; x < _width ; x++ )
    {
        for (float y = 0 ; y < _height ; y++)
        {
            _tiles->at(x).at(y).draw(window);
        }
    }
}

int World::collide(const Character& character) const
{
    int collide_code=0b0;
    if (
            character.getX() < 0 or
            character.getX() > _width * 32.f or
            character.getY() < 0 or
            character.getY() > _height * 32.f or
            _tiles->at((int) (character.getX()/32)).at((int) (character.getY()/32)).isVoid()
       )
    {
        collide_code=0b1;
    }
    return collide_code;
}
