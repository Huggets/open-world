#include "game.hpp"

Game::Game() : _stillRunning(true) {}

Game::~Game() {}

void Game::run() {
    // The game will run until we close the window or if we decide to stop it
    while (_stillRunning and _engine.isWindowOpen()) {
        _engine.frame();
    }
}
