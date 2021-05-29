#ifndef DEF_CHARACTER
#define DEF_CHARACTER

#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "transformable.hpp"

/*
   Represent a game character.
 */
class Character : public Transformable
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
           Moves the acharacter and change its direction according
           to the offsets.

           updatePosition() must be called after this to also update the
           position of the sprite. Otherwise the character will not change
           its position on the screen.
         */
        virtual void move(float offsetX, float offsetY) override;

        /*
           Sets the x and y coordinate of the character and change
           its direction according to them.

           updatePosition() must be called after this to also update the
           position of the sprite. Otherwise the character will not change
           its position on the screen.
         */
        virtual void setPosition(float x, float y) override;

        /*
           Update the position of the sprite's character.
         */
        virtual void updatePosition() override;

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
