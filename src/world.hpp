#ifndef DEF_WORLD
#define DEF_WORLD

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "tile.hpp"

/*
   Represents the world where the characters lives.
 */
class World
{
    public:
        World(
                unsigned int width,
                unsigned int height,
                std::unique_ptr<Tile[]>& tiles
             );

        /*
           Returns the width of the world.
         */
        unsigned int getWidth() const;

        /*
           Returns the heigth of the world.
         */
        unsigned int getHeight() const;

        /*
           Draw the tiles on the window.
         */
        void draw(sf::RenderWindow& window);

    protected:
        /*
           Width of the world.
         */
        unsigned int _width;

        /*
           Height of the world.
         */
        unsigned int _height;

        /*
           Points to the one dimensional array which contains all the tiles
           of the world.
         */
        std::unique_ptr<Tile[]> _tiles;
};

enum Direction
{
    NONE  = 0b0000,
    NORTH = 0b0001,
    SOUTH = 0b0010,
    EAST  = 0b0100,
    WEST  = 0b1000
};

#endif
