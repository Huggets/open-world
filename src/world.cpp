#include "world.hpp"
#include <iostream>

World::World(
        std::unique_ptr<std::vector<std::vector<WorldPiece>>>& worldPieces
        ) :
    _width(0),
    _height(0),
    _worldPieces(std::move(worldPieces))
{
    for (long unsigned int y = 0 ; y < _worldPieces->size() ; y++)
    {
        if (_height < y + 1)
        {
            _height = y + 1;
        }
        for (long unsigned int x = 0 ; x < _worldPieces->at(y).size() ; x++)
        {
            if (_width < x + 1)
            {
                _width = x + 1;
            }
        }
    }
}

unsigned int World::getWidth() const
{
    return _width;
}

unsigned int World::getHeight() const
{
    return _height;
}

void World::draw(sf::RenderWindow& window)
{
    for (float worldX = 0 ; worldX < _width ; worldX++ )
    {
        for (float worldY = 0 ; worldY < _height ; worldY++)
        {
            for (int tileX = 0 ; tileX < 8 ; tileX++)
            {
                for (int tileY = 0 ; tileY < 8 ; tileY++)
                {
                    _worldPieces->at(worldY).at(worldX).drawTile(window, tileX, tileY);
                }
            }
        }
    }
}

bool World::collide(const Character& character) const
{
    float characterX(character.getX());
    float characterY(character.getY());
    unsigned int worldPieceX(
            (unsigned int) (characterX / (WORLDPIECE_SIZE * TILE_SIZE)));
    unsigned int worldPieceY(
            (unsigned int) (characterY / (WORLDPIECE_SIZE * TILE_SIZE)));
    unsigned int tileX(
            (unsigned int) (characterX / TILE_SIZE) - WORLDPIECE_SIZE * worldPieceX);
    unsigned int tileY(
            (unsigned int) (characterY / TILE_SIZE) - WORLDPIECE_SIZE * worldPieceY);
    if (
            characterX < 0 or
            characterX > _width * WORLDPIECE_SIZE * TILE_SIZE or
            characterY < 0 or
            characterY > _height * WORLDPIECE_SIZE * TILE_SIZE or
            _worldPieces->at(worldPieceY).at(worldPieceX).isTileVoid(tileX, tileY)
       )
    {
        return true;
    }
    return false;
}
