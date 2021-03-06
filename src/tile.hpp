#ifndef DEF_TILE
#define DEF_TILE

#include <SFML/Graphics.hpp>

/*
   Represents a single tile of a World.
 */
class Tile
{
    public:
        Tile();

        /*
           Draws the tile on the window.
         */
        void draw(sf::RenderWindow& window) const;

        /*
           Returns the width of the tile.
         */
        float getWidth() const;

        /*
           Returns the height of the tile.
         */
        float getHeight() const;

        /*
           Sets the position of the tile.
         */
        void setPosition(float x, float y);

        /*
           Sets the texture of the tile.
         */
        void setTexture(sf::Texture* texture);

        /*
           TODO Doc
         */
        bool isGround() const;

    protected:
        /*
           The width of the tile.
         */
        float _width;

        /*
           The height of the tile.
         */
        float _height;

        /*
           The x coordinate of the tile.
         */
        float _x;

        /*
           The y coordinate of the tile.
         */
        float _y;

        /*
           TODO Doc
         */
        bool _isGround;

        /*
           The shape that represent the tile.
         */
        sf::RectangleShape _shape;
};

#endif
