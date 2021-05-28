#ifndef DEF_WORLDPIECE
#define DEF_WORLDPIECE

#define WORLDPIECE_SIZE 8

#include "tile.hpp"
#include <SFML/Graphics.hpp>

class WorldPiece{
    public:
        WorldPiece(
                std::unique_ptr<Tile[][WORLDPIECE_SIZE]>& tiles);

        /*
           Returns true if the tile at the corresponding coordinates
           is a void tile.
         */
        bool isTileVoid(unsigned int x, unsigned int y) const;

        /*
           Draws the tile at the corresponding coordinates.
         */
        void drawTile(sf::RenderWindow& window, unsigned int x, unsigned int y) const;
    protected:
        /*
           Tiles contained in the WorldPiece
         */
        std::unique_ptr<Tile[][WORLDPIECE_SIZE]> _tiles;
};

#endif
