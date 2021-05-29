#ifndef DEF_WORLD
#define DEF_WORLD

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "worldpiece.hpp"
#include "character.hpp"

class Character;

/*
   Represents the world where the characters lives.
 */
class World
{
    public:
        World(
                std::unique_ptr<std::vector<std::vector<WorldPiece>>>& worldPieces
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
        void draw(sf::RenderWindow& window, int scrollX, int scrollY);

        /*
           Return true if character is colliding, for example if the
           character is outside the world or is in a void tile
         */
        bool collide(const Character& character) const;

    protected:
        /*
           Width of the world (In number of WorldPieces).
         */
        unsigned int _width;

        /*
           Height of the world (In number of WorldPieces).
         */
        unsigned int _height;

        /*
           Total number of tiles on the width on the world.

           TODO This sentence may be incorrect. Change it to be more
           explanatory.
         */
        unsigned int _tileWidthCount;

        /*
           Total number of tiles on the height on the world.

           TODO This sentence may be incorrect. Change it to be more
           explanatory.
         */
        unsigned int _tileHeightCount;

        /*
           Pointer to an array of WorldPieces which contains all the tiles
           of the world.

           The first index is the y coordinate.
           The second index is the x coordinate.
         */
        std::unique_ptr<std::vector<std::vector<WorldPiece>>> _worldPieces;

        /*
           Offsets the tiles are moving.

           Used to not display every tile.
         */
        int _scrollX;
        int _scrollY;
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
