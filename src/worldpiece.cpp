#include "worldpiece.hpp"

WorldPiece::WorldPiece(
        std::unique_ptr<Tile[][WORLDPIECE_SIZE]>& tiles) :
    tiles(std::move(tiles))
{
}
