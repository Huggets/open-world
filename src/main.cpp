#include <iostream>
#include <cstring>
#include <string>
#include "game.hpp"
#include "console.hpp"

int main(int argc, char** argv)
{
    bool savePerformance(false);
    std::string performanceFilename("data/profiles/profile.latest");
    std::string worldFilename("data/worlds/world1.world");
    float playerX(0);
    float playerY(0);

    for (int i = 1 ; i < argc ; i++)
    {
        // If the argument is -h or --help we display the help menu
        if (
                strcmp(argv[i], "--help") == 0 or
                strcmp(argv[i], "-h") == 0
           )
        {
            std::string message("Usage: ");
            message += argv[0];
            message += " [--help]";
            message += " [--profile FILE]";
            message += " [--world FILE]";
            message += "\n\n";
            message += "  -h, --help         Display this help message\n";
            message += "  -p, --profile FILE Save a performance profile into FILE\n";
            message += "  -w, --world FILE   Load FILE and use it as the playable world\n";
            message += "\n";
            std::cout << message;
            return 0;
        }
        // If the argument is -p or --profile we will store information about
        // performance in a file
        else if (
                strcmp(argv[i], "--profile") == 0
                or strcmp(argv[i], "-p") == 0
                )
        {
            savePerformance = true;

            // If there is an argument after -p or --profile we take it as the
            // profile file
            if (i < argc-1 and strlen(argv[i+1]) != 0)
            {
                performanceFilename =  argv[i+1];
                i++;
            }
        }
        // The world to load
        else if (
                strcmp(argv[i], "--world") == 0
                or strcmp(argv[i], "-w") == 0
                )
        {
            if (i < argc-1 and strlen(argv[i+1]) != 0)
            {
                worldFilename = argv[i+1];
            }
        }
        else if (
                strcmp(argv[i], "--coordinate") == 0
                or strcmp(argv[i], "-c") == 0
                )
        {
            if (i+2 < argc and strlen(argv[i+2]) != 0 and strlen(argv[i+1]) != 0)
            {
                try {
                    playerX = std::stof(argv[i+1]);
                    playerY = std::stof(argv[i+2]);
                }
                catch (std::invalid_argument const&)
                {
                    console::warning("The coordinates given must be numbers!");
                }
            }
        }
    }

    Game game(worldFilename, playerX, playerY);
    game.run(savePerformance, performanceFilename);

    return 0;
}
