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

    // TODO Finish the help menu
    for (int i = 1 ; i < argc ; i++)
    {
        // If the argument is -h or --help we display the help menu
        if (
                strcmp(argv[i], "--help") == 0 or
                strcmp(argv[i], "-h") == 0
           )
        {
            std::cout << "Display help" << std::endl;
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
    }

    Game game(worldFilename);
    game.run(savePerformance, performanceFilename);

    return 0;
}
