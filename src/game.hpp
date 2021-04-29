#ifndef GAME_HPP
#define GAME_HPP

#include "engine.hpp"

/*
   Represent the whole game.

   It contains the engine that handles almost everything (loading ressources,
   drawing on the window, managing characters…)
   */
class Game {
    public:
        Game();
        ~Game();

        /*
           Main function of the game that call each frame function of the engine
           in an infinite loop.
           */
        void run();

    protected:
        /*
           The game engine that handles almost everything.
           */
        Engine _engine;

        /*
           Indicate whether the game is running or not.
           */
        bool _stillRunning;
};

#endif
