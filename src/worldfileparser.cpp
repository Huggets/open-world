#include "worldfileparser.hpp"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "console.hpp"

#define IS_BLANK(x) (x == ' ' or x == '\t' or x == '\n')

/* Defines the mode the parser is in. It corresponds to the section of the file
   (#deftile, #defworld…).
 */
enum class Mode
{
    MODE_ROOT,
    MODE_DEFTILE,
    MODE_DEFWORLD
};

// TODO change variable name and documentation in order to be more
// understandable

std::unique_ptr<World> wfp::parse(
        const std::string filename,
        std::unordered_map<std::string, sf::Texture>& texturesMap
        )
{
    // The world file
    std::fstream worldFile(filename, std::fstream::in);

    // Contains the character we are currently reading in the file
    char c;

    // Contains the last word we are currently reading in the file
    std::string word;

    // Mode of the parser
    Mode mode(Mode::MODE_ROOT);

    // Pointer to the array of the world tiles
    std::unique_ptr<Tile[]> tiles;

    // Used in MODE_TILEDEF
    // Key to the corresponding tile images
    int tileKey(0);

    // Used in MODE_TILEDEF
    // Indicates whether tileKey is set or no
    bool tileKeySet(false);

    // Total size of the world
    unsigned int tilesArraySize(0);


    // Set to true when the world file has defined more tiles
    // than worldWidth * worldHeight
    bool tilesArrayFilled(false);

    // Number of tiles defined in the world file at this moment
    unsigned int tilesCount(0);

    // Used in MODE_DEFWORLD
    // Used to read the worldHeight/worldWidth in the file then to go directly in the
    // corresponding block of code
    bool gettingHeight(true);
    bool gettingWidth(true);

    float worldWidth(0);
    float worldHeight(0);

    // Coordinate of the tile we adding.
    float xTile(0);
    float yTile(0);

    // Returns the name of the tile represented by an int
    std::unordered_map<int, std::string> intsName;

    // Analyzes the content of the file and sets the variables according to it
    // TODO Optimize the code
    if (worldFile.is_open())
    {
        // We read until we are at the end of the file
        while (!worldFile.eof())
        {
            c = worldFile.get();
            if (mode == Mode::MODE_DEFWORLD)
            {
                // Executed when we have the full word
                if (IS_BLANK(c) and !word.empty())
                {
                    if (gettingWidth)
                    {
                        gettingWidth = false;
                        worldWidth = std::stof(word);
                    }
                    else if (gettingHeight)
                    {
                        gettingHeight = false;
                        worldHeight = std::stof(word);
                        // We now have the world width and the world height so
                        // we can create the array of Tiles
                        tilesArraySize = worldWidth * worldHeight;
                        tiles = std::make_unique<Tile[]>(tilesArraySize);
                    }
                    else
                    {
                        if (word == "#fedworld")
                        {
                            mode = Mode::MODE_ROOT;
                        }
                        // We add the intTile to intTiles vector
                        else if (not tilesArrayFilled)
                        {
                            tiles[tilesCount].setTexture(&texturesMap[
                                    intsName[std::stoul(word)]
                            ]);
                            tiles[tilesCount].setPosition(xTile, yTile);
                            xTile += tiles[tilesCount].getWidth();
                            if (xTile/tiles[tilesCount].getWidth() >= worldWidth)
                            {
                                xTile = 0;
                                yTile += tiles[tilesCount].getHeight();
                            }
                            tilesCount++;
                            if (tilesCount >= tilesArraySize)
                            {
                                tilesArrayFilled = true;
                            }
                        }
                    }
                    word.clear();
                }
                else
                {
                    word += c;
                }
            }
            else if (IS_BLANK(c))
            {
                if (!word.empty())
                {
                    if (mode == Mode::MODE_ROOT)
                    {
                        if (word == "#deftile")
                        {
                            mode = Mode::MODE_DEFTILE;
                        }
                        else if (word == "#defworld")
                        {
                            mode = Mode::MODE_DEFWORLD;
                        }
                    }
                    else if (mode == Mode::MODE_DEFTILE)
                    {
                        if (word == "#fedtile")
                        {
                            mode = Mode::MODE_ROOT;
                        }
                        else
                        {
                            if (tileKeySet)
                            {
                                intsName[tileKey] = word;
                                texturesMap[word] = sf::Texture();
                                tileKeySet = !tileKeySet;
                            }
                            else
                            {
                                tileKey = std::stof(word);
                                tileKeySet = !tileKeySet;
                            }
                        }
                    }
                }
                word.clear();
            }
            else
            {
                word += c;
            }
        }
        worldFile.close();
    }
    else
    {
        std::string message("Cannot open world file '");
        message += filename;
        message += "'.";
        console::error(message);
    }

    return std::make_unique<World>(worldWidth, worldHeight, tiles);
}
