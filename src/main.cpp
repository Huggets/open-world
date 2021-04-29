#include <iostream>
#include <cstring>
#include "game.hpp"

int main(int argc, char ** argv) {
    // TODO Finish this menu
    for (int i = 1 ; i < argc ; i++) {
        if (strcmp(argv[i], "--help") == 0 or strcmp(argv[i], "-h") == 0) {
            std::cout << "Display help" << std::endl;
            return 0;
        }
    }

    Game game;
    game.run();

    return 0;
}
