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
class Game
{
    public:
        Game(const std::string& worldFilename);

        /*
           Starts the game.
         */
        void run(bool profile, const std::string& profileConfigName);

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
           Unordored map that store every textures
         */
        std::unordered_map<std::string, sf::Texture>  _textures;

        /*
           The world in which the user currently plays.
         */
        std::unique_ptr<World> _world;

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
           Difference between _startTime and _lastTime.
         */
        int _diffTime;

        /*
           These two variables are used to avoid getting the fps for each
           frame.
           Look at the cpp file for more information.
         */
        int _fpsTime;
        int _fpsTimeTmp;

        /*
           Time the function frame waits at the end of each call.

           For example it can be used in order to have a fps limit.
         */
        int _sleepTime;

        /*
           Defining two person for now.

           TODO Search for an optimized way to create and handle many characters
         */
        Character _person1;
        Character _person2;

        /*
           Points to the character the user controls.
         */
        Character* _playerCharacter;

        /*
           Offset the player moves.
         */
        float _tmpPlayerX;
        float _tmpPlayerY;

        /*
           Speed at which the player moves.
         */
        float moveSpeed;
};

#endif
