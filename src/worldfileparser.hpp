#ifndef DEF_WORLDFILEPARSER
#define DEF_WORLDFILEPARSER

#include <string>
#include "world.hpp"

namespace worldFileParser {
    /* 
       Parses a world file and converts it into a World object.

       Return the converted World.
       */
    World parse(const char fileName[]);
}

#endif
