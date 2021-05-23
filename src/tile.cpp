#include "tile.hpp"

Tile::Tile() :
     _x(0.f),
     _y(0.f),
     _width(32.f),
     _height(32.f),
     _isVoid(true),
    _shape(sf::Vector2f(32.f, 32.f))
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
    _x = x;
    _y = y;
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
