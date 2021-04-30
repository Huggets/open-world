#include <iostream>
#include <cstring>
#include "game.hpp"
#include "console.hpp"

#define PROFILE_FILE "data/profiles/profile.latest"

int main(int argc, char ** argv) {
    bool performanceProfile(false);
    char profileConfigName[255] = PROFILE_FILE;

    // TODO Finish the help menu
    for (int i = 1 ; i < argc ; i++) {
        // If the argument is -h or --help we display the help menu
        if (strcmp(argv[i], "--help") == 0 or strcmp(argv[i], "-h") == 0) {
            std::cout << "Display help" << std::endl;
            return 0;
        
        // If the argument is -p or --profile we will store information about
        // performance in a file
        } else if (
                strcmp(argv[i], "--profile") == 0
                or strcmp(argv[i], "-p") == 0
                ) {
            performanceProfile = true;
            
            // If there is an argument after -p or --profile we take it as the
            // profile file
            if (i+1 < argc and strlen(argv[i+1]) < 256) {
                strcpy(profileConfigName, argv[i+1]);
            }
        }
    }

    Game game;
    game.run(performanceProfile, profileConfigName);

    return 0;
}
