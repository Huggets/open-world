#ifndef DEF_CHARACTER
#define DEF_CHARACTER

#include <SFML/Graphics.hpp>

/*
   Represent a game character.
   */
class Character {
    public:
        Character();

        /*
           Draw the character inside window.
           */
        void draw(sf::RenderWindow &window) const;

        /*
           Set the texture of the character.
           */
        void setTexture(sf::Texture &texture);

        /*
           Move the character according to the offsets.
           */
        void move(int offsetX, int offsetY);

        /*
           Return the x absolute coordinate of the character.
           */
        int getX() const;

        /*
           Return the y absolute coordinate of the character.
           */
        int getY() const;

    protected:
        /*
           The sprite of the character.
           */
        sf::Sprite _sprite;

        /*
           Absolute x coordinate.
           */
        int _x;

        /*
           Absolute y coordinate.
           */
        int _y;
};

#endif
