#ifndef DEF_WORLDFILEPARSER
#define DEF_WORLDFILEPARSER

#include <string>
#include <memory>
#include "world.hpp"

namespace wfp
{
    /* 
       Parses a world file and return the converted world.

       filename is the name of the world file and textures map is the textures
       map of the game in which the texture (not loaded) of the tiles will be
       added.
     */
    std::unique_ptr<World> parse(
            const std::string filename,
            std::unordered_map<std::string, sf::Texture>& texturesMap
            );
}

#endif
