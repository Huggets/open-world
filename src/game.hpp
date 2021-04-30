#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "character.hpp"

/*
   Represent the whole game.
   */
class Game {
    public:
        Game();

        /*
           Start the game.
           */
        void run(bool profile, char *profileConfigName);

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
           Store the texture of a person.
           */
        sf::Texture _personTexture;

        /*
           The font used to display text.
           */
        sf::Font _font;

        /*
           Store the coordinates of the character the player control.
           */
        sf::Text _playerCoordinatesText;

        /*
           Store the the start time of the current _frame function that is being
           executed.
           */
        clock_t _startTime;

        /*
           Store the the start time of the last _frame function that was
           executed.
           */
        clock_t _lastTime;

        /*
           These two variables are used to avoid the update of the fps counter
           each frame.
           Look at the cpp file for more information.
           */
        int _fpsTime;
        int _fpsTimeTmp;

        /*
           Point to the character the user controls.
           */
        Character * _playerCharacter;

        /*
           Defining two person for now.

           TODO Search for an optimized way to create and handle many characters.
           */
        Character _person1;
        Character _person2;

        /*
           The world we play.
           */
        World _world;
};

#endif
