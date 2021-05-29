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
           Tiles contained in the WorldPiece
         */
        std::unique_ptr<Tile[][WORLDPIECE_SIZE]> tiles;
};

#endif
