#ifndef DEF_TILE
#define DEF_TILE

#define TILE_SIZE 32.f

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
           Return true if the tile is a void tile.
         */
        bool isVoid() const;

        /*
           Define whether it is a void tile or no.
         */
        void setIsVoid(bool isVoid);

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
           Whether the tile is a void tile or no.
         */
        bool _isVoid;

        /*
           The shape that represent the tile.
         */
        sf::RectangleShape _shape;
};

#endif
