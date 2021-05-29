#ifndef DEF_TILE
#define DEF_TILE

#define TILE_SIZE 32.f

#include <SFML/Graphics.hpp>
#include "transformable.hpp"

/*
   Represents a single tile of a World.
 */
class Tile : public Transformable
{
    public:
        Tile();

        /*
           Moves the tile according to the offsets.
         */
        virtual void move(float offsetX, float offsetY) override;

        /*
           Sets the x and y coordinate of the tile;
         */
        virtual void setPosition(float x, float y) override;

        /*
           Update the position of the shape's tile.
         */
        virtual void updatePosition() override;

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
           The shape that represent the tile.
         */
        sf::RectangleShape _shape;

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
};

#endif
