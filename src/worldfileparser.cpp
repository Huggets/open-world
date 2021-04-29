#include <fstream>
#include "worldfileparser.hpp"

void WorldFileParser::parse(std::string fileName) {
    std::fstream worldFile;
    char c;

    worldFile.open(fileName, std::fstream::in);
    c = worldFile.get();
    
    while (c != EOF) {
        c = worldFile.get();
    }
}
