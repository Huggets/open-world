#include "world.hpp"
#include "game.hpp"
#include <iostream>

World::World(
        std::unique_ptr<std::vector<std::vector<WorldPiece>>>& worldPieces
        ) :
    _width(0),
    _height(0),
    _worldPieces(std::move(worldPieces)),
    _scrollX(0),
    _scrollY(0)
{
    // Setting the height and width of the world
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

    _tileWidthCount = _width * WORLDPIECE_SIZE * TILE_SIZE;
    _tileHeightCount = _height * WORLDPIECE_SIZE * TILE_SIZE;
}

unsigned int World::getWidth() const
{
    return _width;
}

unsigned int World::getHeight() const
{
    return _height;
}

void World::draw(sf::RenderWindow& window, int scrollX, int scrollY)
{
    bool isScrolling(scrollX != _scrollX or scrollY != _scrollY);
    _scrollX = scrollX;
    _scrollY = scrollY;
    int minWorldPieceX = _scrollX / TILE_SIZE / WORLDPIECE_SIZE - 1;
    int minWorldPieceY = _scrollY / TILE_SIZE / WORLDPIECE_SIZE - 1;
    int maxWorldPieceX = ((_scrollX + WINDOW_WIDTH) / TILE_SIZE) / WORLDPIECE_SIZE;
    int maxWorldPieceY = ((_scrollY + WINDOW_HEIGHT) / TILE_SIZE) / WORLDPIECE_SIZE;
    if (minWorldPieceX < 0)
    {
        minWorldPieceX = 0;
    }
    if (minWorldPieceY < 0)
    {
        minWorldPieceY = 0;
    }
    if (maxWorldPieceX > (int) _width - 1)
    {
        maxWorldPieceX = _width - 1;
    }
    if (maxWorldPieceY > (int) _height - 1)
    {
        maxWorldPieceY = _height - 1;
    }

    if (isScrolling)
    {
        for (int x = minWorldPieceX ; x <= maxWorldPieceX ; x++)
        {
            for (int  y = minWorldPieceY ; y <= maxWorldPieceY ; y++)
            {
                for (int tileX = 0 ; tileX < 8 ; tileX++)
                {
                    for (int tileY = 0 ; tileY < 8 ; tileY++)
                    {
                        _worldPieces->at(y).at(x).tiles[tileX][tileY].scroll(
                                _scrollX,
                                _scrollY);
                        _worldPieces->at(y).at(x).tiles[tileX][tileY].updatePosition();
                        _worldPieces->at(y).at(x).tiles[tileX][tileY].draw(window);
                    }
                }
            }
        }
    }
    else
    {
        for (int x = minWorldPieceX ; x <= maxWorldPieceX ; x++)
        {
            for (int  y = minWorldPieceY ; y <= maxWorldPieceY ; y++)
            {
                for (int tileX = 0 ; tileX < 8 ; tileX++)
                {
                    for (int tileY = 0 ; tileY < 8 ; tileY++)
                    {
                        _worldPieces->at(y).at(x).tiles[tileX][tileY].draw(window);
                    }
                }
            }
        }
    }
}

bool World::collide(const Character& character) const
{
    unsigned int worldPieceX(
            (unsigned int) (character.getX() / (WORLDPIECE_SIZE * TILE_SIZE)));
    unsigned int worldPieceY(
            (unsigned int) (character.getY() / (WORLDPIECE_SIZE * TILE_SIZE)));
    unsigned int tileX(
            (unsigned int) (character.getX() / TILE_SIZE) - WORLDPIECE_SIZE * worldPieceX);
    unsigned int tileY(
            (unsigned int) (character.getY() / TILE_SIZE) - WORLDPIECE_SIZE * worldPieceY);
    if (
            character.getX() < 0 or
            character.getX() > _width * WORLDPIECE_SIZE * TILE_SIZE or
            character.getY() < 0 or
            character.getY() > _height * WORLDPIECE_SIZE * TILE_SIZE or
            _worldPieces->at(worldPieceY).at(worldPieceX).tiles[tileX][tileY].isVoid()
       )
    {
        return true;
    }
    return false;
}
