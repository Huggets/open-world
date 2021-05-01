#include "game.hpp"
#include <cstring>
#include <ctime>
#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <thread>
#include "console.hpp"
#include "worldfileparser.hpp"

#define NEW_TEXTURE std::unique_ptr<sf::Texture>(new sf::Texture)
#define PNG_PERSON "data/images/person.png"
#define FONT_LINBIOLUM "data/fonts/linbiolum.otf"
#define WORLD_CONFIG "data/worlds/world1.world"

Game::Game() :
    _window(sf::VideoMode(800, 600), "Open World", sf::Style::Close),
    _textures(),
    _font(),
    _playerCoordinatesText(),
    _fpsText(),
    _startTime(clock()),
    _lastTime(_startTime),
    _fpsTime(0),
    _fpsTimeTmp(0),
    _sleepTime(0),
    _playerCharacter(&_person1),
    _person1(),
    _person2()
{
    // Loading files
    _textures["person"] = NEW_TEXTURE;
    _textures["person"]->loadFromFile(PNG_PERSON);
    _textures["dirt"] = NEW_TEXTURE;
    _textures["dirt"]->loadFromFile("data/images/dirt.png");
    _font.loadFromFile(FONT_LINBIOLUM);

    _person1.setTexture(*_textures["person"]);
    _person2.setTexture(*_textures["dirt"]);
    _playerCoordinatesText.setFont(_font);
    _playerCoordinatesText.setPosition(0, 570);
    _playerCoordinatesText.setFillColor(sf::Color::Black);
    _fpsText.setFont(_font);
    _fpsText.setPosition(0, 0);
    _fpsText.setFillColor(sf::Color::Black);
    _fpsText.setString("nothing");
}

void Game::run(bool profile, char profileConfigName[]) {
    // Each time we save the fps we add it in fpsTotal
    unsigned long int fpsTotal(0);
    // Number of fps saved
    unsigned int fpsTotalCount(0);
    // We will store the information about the performance in a file
    std::fstream profileFile(profileConfigName, std::fstream::in | std::fstream::app);
    // Contains all the fps saved
    std::queue<int> fps;

    if (profile and profileFile.is_open()) {
        console::info(std::string(
                    "Performance information will be saved in the file "
                    ).append(profileConfigName).c_str());
        while (_window.isOpen()) {
            _frame();
    
            // We save the fps each half second
            _fpsTimeTmp = (float) _startTime/ CLOCKS_PER_SEC * 2;
            if (_fpsTimeTmp > _fpsTime) {
                _fpsTime = _fpsTimeTmp;
                int n = 1 / ((float) (_startTime - _lastTime) / CLOCKS_PER_SEC);
                fps.push(n);
                fpsTotalCount++;
                fpsTotal += n;
                _fpsText.setString(std::to_string(n));
            }
        } 

        // Writing all fps and fps average into the profile file
        profileFile.put('\n');
        for ( ; !fps.empty() ; ) {
            profileFile << fps.front() << ' ';
            fps.pop();
        }
        if (fpsTotalCount == 0) {
            profileFile << "Average: " << 0;
        } else {
            profileFile << "Average: " << fpsTotal / fpsTotalCount;
        }
        profileFile.close();
    } else {
        while (_window.isOpen()) {
            _frame();
        }
    }
}

// As this function is executed each frame, we need to have the best
// performance. So we inline it to avoid a function call
inline void Game::_frame() {
    _lastTime = _startTime;
    _startTime = clock();
    int diffTime = _startTime-_lastTime;

    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
    }

    /*
       Misc part

       TODO Change the name of this part to be more explanatory
       */
    _playerCoordinatesText.setString(
            "X: " + std::to_string(_playerCharacter->getX()) +
            ", Y: " + std::to_string(_playerCharacter->getY()
                ));
    _fpsText.setString(std::to_string(
                (int) ( 1 / (float) ((float)(diffTime + _sleepTime) / (float)CLOCKS_PER_SEC) )
                ));

    /*
       Input part
       */
    // The character moves 10 pixels per second in the corresponding direction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _playerCharacter->move(-150*
                (float) ((float)(diffTime + _sleepTime) / (float)CLOCKS_PER_SEC)
                , 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _playerCharacter->move(150*
                (float) ((float)(diffTime + _sleepTime) / (float)CLOCKS_PER_SEC)
                , 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _playerCharacter->move(0,
                150*(float) ((float)(diffTime + _sleepTime) / (float)CLOCKS_PER_SEC)
                );
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _playerCharacter->move(0,
                -150*(float) ((float)(diffTime + _sleepTime) / (float)CLOCKS_PER_SEC)
                );
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        // The user now controls _person1
        _playerCharacter = &_person1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        // The user now controls _person2
        _playerCharacter = &_person2;
    }

    /*
       Display part
       */
    _window.clear(sf::Color::White);

    _person1.draw(_window);
    _person2.draw(_window);
    _window.draw(_playerCoordinatesText);
    _window.draw(_fpsText);

    _window.display();

    /*
       Sleep a certain amount of time in order to have a fps limit
       */
    _sleepTime = int (1.f / 60 * CLOCKS_PER_SEC - diffTime);
    std::this_thread::sleep_for(
            std::chrono::duration<int, std::ratio<1, CLOCKS_PER_SEC>>(_sleepTime)
            );
}
