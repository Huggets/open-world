#include "worldpiece.hpp"

WorldPiece::WorldPiece(
        std::unique_ptr<Tile[][WORLDPIECE_SIZE]>& tiles) :
    _tiles(std::move(tiles))
{
}

bool WorldPiece::isTileVoid(unsigned int x, unsigned int y) const
{
    return _tiles[x][y].isVoid();
}


void WorldPiece::drawTile(sf::RenderWindow& window, unsigned int x, unsigned int y) const
{
    _tiles[x][y].draw(window);
}
