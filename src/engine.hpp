#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "character.hpp"

/*
   Manage inputs, display, characters, settings…
   */
class Engine {
    public:
        Engine();

        /*
           Method that will be executed each frame of the game.
           */
        void frame();

        /*
           Return true if the main window of the game is open.
           */
        bool isWindowOpen() const;

    protected:
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
           Store the displayed frame per second.
           */
        sf::Text _fps;

        /*
           Store the the start time of the current frame function that is being
           executed.
           */
        clock_t _startTime;

        /*
           Store the the start time of the last frame function that was
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
