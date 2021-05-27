#ifndef DEF_CHARACTER
#define DEF_CHARACTER

#include <SFML/Graphics.hpp>
#include "world.hpp"

/*
   Represent a game character.
 */
class Character
{
    public:
        Character();

        /*
           Draws the character inside window.
         */
        void draw(sf::RenderWindow& window) const;

        /*
           Sets the texture of the character.
         */
        void setTexture(sf::Texture& texture);

        /*
           Moves the character and change its direction according
           to the offsets.
         */
        void move(float offsetX, float offsetY);

        /*
           Sets the x and y coordinate of the character and change
           its direction according to them.
         */
        void setPosition(float x, float y);

        /*
           Returns the x absolute coordinate of the character.
         */
        float getX() const;

        /*
           Returns the y absolute coordinate of the character.
         */
        float getY() const;

        /*
           Returns the height of the sprite
         */
        float getHeight() const;

        /*
           Returns the width of the sprite
         */
        float getWidth() const;

    protected:
        /*
           The sprite of the character.
         */
        sf::Sprite _sprite;
};

#endif
