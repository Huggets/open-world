#include "transformable.hpp"

Transformable::Transformable() :
    _x(0),
    _y(0),
    _scrollX(0),
    _scrollY(0)
{
}

void Transformable::scroll(int scrollX, int scrollY)
{
    _scrollX = scrollX;
    _scrollY = scrollY;
}

float Transformable::getX() const
{
    return _x;
}

float Transformable::getY() const
{
    return _y;
}
