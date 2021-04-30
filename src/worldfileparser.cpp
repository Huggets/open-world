#include <fstream>
#include <iostream>
#include <queue>
#include "worldfileparser.hpp"

void worldFileParser::parse(std::string fileName) {
    std::fstream worldFile;
    char c;
    std::string word;

    worldFile.open(fileName, std::fstream::in);
    c = worldFile.get();
    while (c != EOF) {
        word += c;
//        if (c == ' ' or 
        c = worldFile.get();
    }
}
