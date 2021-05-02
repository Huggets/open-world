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
// The default mode. When the parser is in this mode, it searches a section
// keyword
#define MODE_ROOT 0
// The mode corresponding to #deftile
#define MODE_DEFTILE 1
// The mode corresponding to #defworld
#define MODE_DEFWORLD 2

World worldFileParser::parse(const char fileName[]) {
    // The world file
    std::fstream worldFile(fileName, std::fstream::in);

    // Contains the character we are currently reading in the file
    char c;

    // Contains the last word we are currently reading in the file
    std::string word;

    // Mode of the parser
    int mode(MODE_ROOT);

    // A std::map that contains all tile images
    std::unique_ptr<std::unordered_map<int, std::string>> tileMap =
        std::make_unique<std::unordered_map<int, std::string>>();

    // Used in MODE_TILEDEF
    // Key to the corresponding tile images
    int tileKey;

    // Used in MODE_TILEDEF
    // Indicates whether tileKey is set or no
    bool tileKeySet(false);

    // Height and width total size of the world
    unsigned int tileArrayHeight(0);
    unsigned int tileArrayWidth(0);
    unsigned int tileArraySize(0);

    bool tileArrayOverflow(false);

    // Contains all tiles of the world
    // Point to an array
    std::unique_ptr<int[]> tileArray(nullptr);

    // Number of tile set in tileArray
    unsigned int tileArrayNb(0);

    // Used in MODE_DEFWORLD
    // Used to read the height/width in the file then to go directly in the
    // corresponding block of code
    bool gettingHeight(true);
    bool gettingWidth(true);

    // Analyzes the content of the file and sets the variables according to it
    // TODO Optimize the code
    if (worldFile.is_open()) {
        while (!worldFile.eof()) {
            c = worldFile.get();
            if (mode == MODE_DEFWORLD) {
                if (IS_BLANK(c) and !word.empty()) {
                    if (gettingWidth) {
                        gettingWidth = false;
                        tileArrayWidth = std::stoi(word);
                    }
                    else if (gettingHeight) {
                        gettingHeight = false;
                        tileArrayHeight = std::stoi(word);
                        // We now have the world width and the world height so
                        // we can create the world array
                        tileArraySize = tileArrayWidth * tileArrayHeight;
                        tileArray = std::make_unique<int[]>(tileArraySize);
                        // Setting all tile to 0 as default
                        // TODO Add the possibility to change the default tile
                        for (int i = tileArraySize-1 ; i >= 0 ; i--) {
                            tileArray[i] = 0;
                        }
                    }
                    else {
                        if (word == "#fedworld") {
                            mode = MODE_ROOT;
                        }
                        else if (not tileArrayOverflow) {
                            tileArray[tileArrayNb] = std::stoi(word);
                            tileArrayNb++;
                            if (tileArrayNb > tileArraySize) {
                                tileArrayOverflow = true;
                                console::warning("WorldFileParser: Size of world\
 than width and/or height. Ignoring next tiles.");
                            }
                        }
                    }
                }
            }
            if (IS_BLANK(c)) {
                if (!word.empty()) {
                    switch (mode) {
                        case (MODE_ROOT):
                            if (word == "#deftile") {
                                mode = MODE_DEFTILE;
                            }
                            else if (word == "#defworld") {
                                mode = MODE_DEFWORLD;
                            }
                            break;

                        case (MODE_DEFTILE):
                            if (word == "#fedtile") {
                                mode = MODE_ROOT;
                            }
                            else {
                                if (tileKeySet) {
                                    (*tileMap)[tileKey] = word;
                                    tileKeySet = !tileKeySet;
                                }
                                else {
                                    tileKey = std::stoi(word);
                                    tileKeySet = !tileKeySet;
                                }
                            }
                            break;
                    }
                }
                word.clear();
            }
            else {
                word += c;
            }
        }
        worldFile.close();
    }
    // If we can't read the file we return an empty World
    else {
        console::error(std::string("Cannot load file ").append(fileName).c_str());
        return World(0, 0, tileArray.release(), tileMap.release());
    }


    return World(tileArrayWidth, tileArrayHeight, tileArray.release(), tileMap.release());
}
