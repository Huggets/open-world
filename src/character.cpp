#include "character.hpp"
#include <iostream>

Character::Character() :
    _sprite()
{
    _sprite.setPosition(0,0);
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

    _sprite.move(offsetX, offsetY);
}

void Character::setPosition(float x, float y)
{
    int direction = Direction::NONE;
    sf::Vector2f spritePos = _sprite.getPosition();
    if (x < spritePos.x)
    {
        direction = Direction::WEST;
    }
    else if (x > spritePos.x)
    {
        direction = Direction::EAST;
    }
    if (y < spritePos.y)
    {
        direction =  static_cast<int>(Direction::NORTH) + direction;
    }
    else if (y > spritePos.y)
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

    _sprite.setPosition(x, y);
}

float Character::getX() const
{
    return _sprite.getPosition().x;
}

float Character::getY() const
{
    return _sprite.getPosition().y;
}

float Character::getHeight() const
{
    return _sprite.getTextureRect().height;
}

float Character::getWidth() const
{
    return _sprite.getTextureRect().width;
}
