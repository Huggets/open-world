#include "tile.hpp"

Tile::Tile() :
    Transformable(),
    _shape(sf::Vector2f(TILE_SIZE, TILE_SIZE)),
     _width(TILE_SIZE),
     _height(TILE_SIZE),
     _isVoid(true)
{
}

void Tile::move(float offsetX, float offsetY)
{
    _x += offsetX;
    _y += offsetY;
}

void Tile::setPosition(float x, float y)
{
    _x = x;
    _y = y;
}

void Tile::updatePosition()
{
    _shape.setPosition(_x - _scrollX, _y - _scrollY);
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
