#include "worldfileparser.hpp"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "console.hpp"

// TODO change variable name and documentation in order to be more
// understandable

std::unique_ptr<World> wfp::parse(
        const std::string filename,
        std::unordered_map<std::string, sf::Texture>& textures
        )
{
    // The world file
    std::fstream worldFile(filename, std::fstream::in);

    // The current character that is read
    char c;

    // The word that is read
    std::string word;

    // Array of tiles defined in the world file
    std::unique_ptr<std::vector<std::vector<Tile>>> tiles;

    // height of the world defined in the world file
    unsigned int worldHeight(0);

    // width of the world defined in the world file
    unsigned int worldWidth(0);

    // Store the properties of a tile. The key is the id of the tile
    std::unordered_map<int, wfp::TileProperties> tilesProperties;
    
    // TILE PROPERTY NAME
    const std::string PROP_TEXTURE_NAME("textureName");
    const std::string PROP_IS_VOID("isVoid");

    // VARIABLE OF deftile LABEL
    bool tileIdIsSet(false);
    int tileArgCount(0);
    unsigned int tileId(0);
    std::string tileTextureName;
    bool tileIsVoid(false);

    // VARIABLE OF defworld LABEL
    bool worldHeightIsSet(false);
    bool worldWidthIsSet(false);
    unsigned int rowSize(0);
    unsigned int tilesCount(0);
    unsigned int tileX(0);
    unsigned int tileY(0);


    // Analyzes the content of the file and sets the variables according to it
    if (worldFile.is_open())
    {
start:
        while (not worldFile.eof())
        {
            c = worldFile.get();
            if (c == ' ' or c == '\t' or c == '\n')
            {
                // It means we have a complete word
                if (word == "StartTiles")
                {
                    word.clear();
                    goto deftile;
                }
                else if (word == "StartWorld")
                {
                    word.clear();
                    goto defworld;
                }
                else
                {
                    word.clear();
                }
            }
            else
            {
                word += c;
            }
        }

        goto end;

deftile:
        while (not worldFile.eof())
        {
            c = worldFile.get();
            if (tileIdIsSet)
            {
                if (c == ' ' or c == '\t' or c == '\n')
                {
                    // Get the tile texture name
                    if (tileArgCount == 0 and not word.empty())
                    {
                        tileTextureName = word;
                        tileArgCount++;
                    }
                    else if (tileArgCount == 1 and not word.empty())
                    {
                        if (word == "true")
                        {
                            tileIsVoid = true;
                        }
                    }

                    // If it is an end of line, add the tile definition
                    // and reset to find another definition or the end
                    if (c == '\n')
                    {
                        if (not tileTextureName.empty())
                        {
                            tilesProperties[tileId].textureName = tileTextureName;
                            textures[tileTextureName] = sf::Texture();
                        }
                        tilesProperties[tileId].isVoid = tileIsVoid;
                        tileIdIsSet = false;
                        tileIsVoid = false;
                        tileArgCount = 0;
                        tileTextureName.clear();
                    }
                    word.clear();
                }
                else
                {
                    word += c;
                }
            }
            else
            {
                // Get the tile id
                if (c == ':')
                {
                    tileId = std::stoul(word);
                    tileIdIsSet = true;
                    word.clear();
                }
                else if (c == ' ' or c == '\t' or c == '\n')
                {
                    // End of tiles definition
                    if (word == "EndTiles")
                    {
                        word.clear();
                        goto start;
                    }
                    // TODO Make exception for this
                    console::error("World file: syntax error");
                    throw std::exception();
                }
                else
                {
                    word += c;
                }
            }
        }

        goto end;

defworld:
        while (not worldFile.eof())
        {
            c = worldFile.get();

            if (c == ' ' or c == '\t' or c == '\n')
            {
                if (word == "EndWorld")
                {
                    word.clear();
                    goto start;
                }

                if (not worldWidthIsSet)
                {
                    worldWidth = std::stoul(word);
                    worldWidthIsSet = true;
                    word.clear();
                }
                else if (not worldHeightIsSet)
                {
                    worldHeight = std::stoul(word);
                    worldHeightIsSet = true;
                    tiles = std::make_unique<std::vector<std::vector<Tile>>>();
                    for (unsigned int y = 0 ; y < worldHeight ; y++)
                    {
                        tiles->push_back(std::vector<Tile>());
                        for (unsigned int x = 0 ; x < worldWidth ; x++)
                        {
                            tiles->at(y).push_back(Tile());
                        }
                    }
                    word.clear();
                }
                else
                {
                    if (word.empty())
                    {
                        // TODO Optimize this to avoid repetition below
                        if (c == '\n' and rowSize < worldWidth)
                        {
                                // TODO Make exception for this
                                console::error("World file: row not fully defined");
                                throw std::exception();
                        }
                    }
                    else
                    {
                        rowSize++;

                        if (c == '\n')
                        {
                            if (rowSize > worldWidth)
                            {
                                // TODO Make exception for this
                                console::error("World file: exceeding world width");
                                throw std::exception();
                            }
                            else if (rowSize < worldHeight)
                            {
                                // TODO Make exception for this
                                console::error("World file: row not fully defined");
                                throw std::exception();
                            }
                            rowSize = 0;
                        }

                        Tile* currentTile = &(tiles->at(tileX).at(tileY));

                        currentTile->setTexture(&textures[
                                tilesProperties[std::stoul(word)].textureName]);
                        currentTile->setIsVoid(
                                tilesProperties[std::stoul(word)].isVoid);
                        currentTile->setPosition(
                                tileX*currentTile->getWidth(),
                                tileY*currentTile->getHeight());
                        tileX++;
                        if (tileX >= worldWidth)
                        {
                            tileX = 0;
                            tileY++;
                        }
                        tilesCount++;
                        word.clear();
                    }
                }
            }
            else
            {
                word += c;
            }
        }

        goto end;

end:
        worldFile.close();
    }
    else
    {
        // TODO Make exception for this
        std::string message("Cannot open '");
        message += filename;
        message += "' file.";
        console::error(message);
    }

    return std::make_unique<World>(worldWidth, worldHeight, tiles);
}
