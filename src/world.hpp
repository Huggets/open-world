#ifndef DEF_WORLD
#define DEF_WORLD

#include <memory>
#include <unordered_map>
#include <string>

/*
   Represents the world where the characters lives.
   */
class World {
    public:
        World(
                int width,
                int height,
                int tileArray[],
                std::unordered_map<int, std::string>* tileConverter
                );

        /*
           Returns the width of the world.
           */
        int getWidth() const;

        /*
           Returns the heigth of the world.
           */
        int getHeight() const;

        /*
           Returns the tile at the given coordinate.

           Returns the default tile (0 for now), if we try to access a tile
           which is outside the world.
           */
        int getTile(int x, int y) const;

        /*
           Returns the name of the ressource corresponding to the tile.
           */
        std::string getTileRessource(int tileKey) const;

    protected:
        /*
           Width of the world.
           */
        int _width;

        /*
           Height of the world.
           */
        int _height;

        /*
           Points to the array which contains all the tiles of the world.
           */
        std::unique_ptr<int[]> _tileArray;

        /*
           The key is the number of the tile and the string is the name of the
           corresponding texture.
           */
        std::unique_ptr<std::unordered_map<int, std::string>> _tileConverter;
};

#endif
