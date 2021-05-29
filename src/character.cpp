#include "character.hpp"

Character::Character() :
    Transformable(),
    _sprite()
{
    _sprite.setPosition(_x, _y);
}

void Character::draw(sf::RenderWindow& window) const
{
    window.draw(_sprite);
}

void Character::setTexture(sf::Texture& texture)
{
    _sprite.setTexture(texture);
    _sprite.setOrigin(
            _sprite.getTextureRect().width/2,
            _sprite.getTextureRect().height/2
            );
}

void Character::move(float offsetX, float offsetY)
{
    int direction = Direction::NONE;
    if (offsetX < 0)
    {
        direction = Direction::WEST;
    }
    else if (offsetX > 0)
    {
        direction = Direction::EAST;
    }
    if (offsetY < 0)
    {
        direction =  static_cast<int>(Direction::NORTH) + direction;
    }
    else if (offsetY > 0)
    {
        direction = static_cast<int>(Direction::SOUTH) + direction;
    }

    switch (direction)
    {
        case (Direction::NORTH):
            _sprite.setRotation(0);
            break;
        case (Direction::SOUTH):
            _sprite.setRotation(180);
            break;
        case (Direction::EAST):
            _sprite.setRotation(90);
            break;
        case (Direction::WEST):
            _sprite.setRotation(-90);
            break;
        case (Direction::NORTH | Direction::EAST):
            _sprite.setRotation(45);
            break;
        case (Direction::NORTH | Direction::WEST):
            _sprite.setRotation(-45);
            break;
        case (Direction::SOUTH | Direction::EAST):
            _sprite.setRotation(135);
            break;
        case (Direction::SOUTH | Direction::WEST):
            _sprite.setRotation(-135);
            break;
        default:
            break;
    }

    _x += offsetX;
    _y += offsetY;
}

void Character::setPosition(float x, float y)
{
    int direction = Direction::NONE;
    if (x < _x)
    {
        direction = Direction::WEST;
    }
    else if (x > _x)
    {
        direction = Direction::EAST;
    }
    if (y < _y)
    {
        direction =  static_cast<int>(Direction::NORTH) + direction;
    }
    else if (y > _y)
    {
        direction = static_cast<int>(Direction::SOUTH) + direction;
    }

    switch (direction)
    {
        case (Direction::NORTH):
            _sprite.setRotation(0);
            break;
        case (Direction::SOUTH):
            _sprite.setRotation(180);
            break;
        case (Direction::EAST):
            _sprite.setRotation(90);
            break;
        case (Direction::WEST):
            _sprite.setRotation(-90);
            break;
        case (Direction::NORTH | Direction::EAST):
            _sprite.setRotation(45);
            break;
        case (Direction::NORTH | Direction::WEST):
            _sprite.setRotation(-45);
            break;
        case (Direction::SOUTH | Direction::EAST):
            _sprite.setRotation(135);
            break;
        case (Direction::SOUTH | Direction::WEST):
            _sprite.setRotation(-135);
            break;
        default:
            break;
    }

    _x = x;
    _y = y;
}

void Character::updatePosition()
{
    _sprite.setPosition(_x - _scrollX, _y - _scrollY);
}

float Character::getHeight() const
{
    return _sprite.getTextureRect().height;
}

float Character::getWidth() const
{
    return _sprite.getTextureRect().width;
}
