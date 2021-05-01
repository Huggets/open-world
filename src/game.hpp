#ifndef GAME_HPP
#define GAME_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "character.hpp"

/*
   Represents the entire game.
   */
class Game {
    public:
        Game();

        /*
           Starts the game.
           */
        void run(bool profile, char profileConfigName[]);

    protected:
        /*
           Method that will be executed each frame of the game.
           */
        inline void _frame();

        /*
           The main window that display the game.
           */
        sf::RenderWindow _window;

        /*
           Unordored map that store every textures
           */
        std::unordered_map<std::string, std::unique_ptr<sf::Texture>>  _textures;

        /*
           The font used to display text.
           */
        sf::Font _font;

        /*
           Stores the coordinates of the character the player control.
           */
        sf::Text _playerCoordinatesText;

        /*
           Text that displays the frames per seconds.
           */
        sf::Text _fpsText;

        /*
           Stores the processor time consumed at the start of the current
           _frame function that is executed.
           */
        clock_t _startTime;

        /*
           Stores the processor time consumed at the start of the last
           _frame function that was executed.
           */
        clock_t _lastTime;

        /*
           These two variables are used to avoid getting the fps for each
           frame.
           Look at the cpp file for more information.
           */
        int _fpsTime;
        int _fpsTimeTmp;

        /*
           Time the function frame waits at the end of each call in order to
           have a fps limit.
           */
        int _sleepTime;

        /*
           Points to the character the user controls.
           */
        Character* _playerCharacter;

        /*
           Defining two person for now.

           TODO Search for an optimized way to create and handle many characters
           */
        Character _person1;
        Character _person2;
};

#endif
