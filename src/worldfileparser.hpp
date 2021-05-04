#ifndef DEF_WORLDFILEPARSER
#define DEF_WORLDFILEPARSER

#include <string>
#include "world.hpp"

namespace wfp
{
    /* 
       Parses a world file.

       Once the parsing is done, width is set to the world width, height 
       is set to the world height, intTiles is set to a vector of one
       dimension which represents all the tile of the world (as integers)
       and tileMap to an std::unordered_map that make the connection between
       an int (which represents the tile) and a string (which holds the
       texture name of the tile).

       TODO Maybe improve this doc
     */
    void parse(
            const std::string filename,
            float& width,
            float& height,
            std::vector<int>& intTiles,
            std::unique_ptr<std::unordered_map<int, std::string>>& tileMap
            );
}

#endif
