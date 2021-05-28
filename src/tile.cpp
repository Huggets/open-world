#include "tile.hpp"

Tile::Tile() :
     _width(TILE_SIZE),
     _height(TILE_SIZE),
     _isVoid(true),
    _shape(sf::Vector2f(TILE_SIZE, TILE_SIZE))
{
}

void Tile::draw(sf::RenderWindow& window) const
{
    window.draw(_shape);
}

float Tile::getWidth() const
{
    return _width;
}

float Tile::getHeight() const
{
    return _height;
}

void Tile::setPosition(float x, float y)
{
    _shape.setPosition(x, y);
}

void Tile::setTexture(sf::Texture* texture)
{
    _shape.setTexture(texture);
}

bool Tile::isVoid() const
{
    return _isVoid;
}

void Tile::setIsVoid(bool isVoid)
{
    _isVoid = isVoid;
}
