#include "character.hpp"

Character::Character() :
    _x(0),
    _y(0)
{
}

void Character::draw(sf::RenderWindow &window) const {
    window.draw(_sprite);
}

void Character::setTexture(sf::Texture &texture) {
    _sprite.setTexture(texture);
}

void Character::move(int offsetX, int offsetY) {
    _x = _x + offsetX;
    _y = _y + offsetY;
    _sprite.move(offsetX, offsetY);
}

int Character::getX() const {
    return _x;
}

int Character::getY() const {
    return _y;
}
