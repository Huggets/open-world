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
           Moves the character according to the offsets.
         */
        void move(float offsetX, float offsetY);

        /*
           Returns the x absolute coordinate of the character.
         */
        float getX() const;

        /*
           Returns the y absolute coordinate of the character.
         */
        float getY() const;

    protected:
        /*
           The sprite of the character.
         */
        sf::Sprite _sprite;
};

#endif
