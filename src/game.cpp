#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <queue>
#include "game.hpp"
#include "console.hpp"
#include "worldfileparser.hpp"

#define PNG_PERSON "data/images/person.png"
#define FONT_LINBIOLUM "data/fonts/linbiolum.otf"
#define WORLD_CONFIG "data/worlds/world1.world"

Game::Game() :
    _window(sf::VideoMode(800, 600), "Open World", sf::Style::Close),
    _personTexture(),
    _font(),
    _playerCoordinatesText(),
    _startTime(clock()),
    _lastTime(_startTime),
    _fpsTime(0),
    _fpsTimeTmp(0),
    _playerCharacter(NULL),
    _person1(),
    _person2(),
    _world()
{
    // The user control _person1
    _playerCharacter = &_person1;

    // Load files
    _personTexture.loadFromFile(PNG_PERSON);
    _font.loadFromFile(FONT_LINBIOLUM);

    worldFileParser::parse(WORLD_CONFIG);

    _person1.setTexture(_personTexture);
    _person2.setTexture(_personTexture);
    _playerCoordinatesText.setFont(_font);
    _playerCoordinatesText.setPosition(0, 570);
    _playerCoordinatesText.setFillColor(sf::Color::Black);
}

void Game::run(bool profile, char *profileConfigName) {
    // Each time we save the fps we add it in fpsTotal
    unsigned long int fpsTotal(0);
    // Number of fps saved
    unsigned int fpsTotalCount(0);
    // We will store the information about the performance in a file
    std::fstream profileFile(profileConfigName, std::fstream::in | std::fstream::app);
    // Contain all the fps saved
    std::queue<int> fps;

    if (profile and profileFile.is_open()) {
        console::info("Profiling performance");
        while (_window.isOpen()) {
            _frame();
    
            // We save the fps each half second
            _fpsTimeTmp = (float) _startTime/ CLOCKS_PER_SEC * 2;
            if (_fpsTimeTmp > _fpsTime) {
                _fpsTime = _fpsTimeTmp;
                fps.push((1 / ((float) (_startTime - _lastTime) / CLOCKS_PER_SEC)));
                fpsTotalCount++;
                fpsTotal += fps.back();
            }
        } 

        // Writing all fps and fps average into the profile file
        profileFile.put('\n');
        for ( ; !fps.empty() ; ) {
            profileFile << fps.front() << ' ';
            fps.pop();
        }
        profileFile << "Average: " << fpsTotal / fpsTotalCount;
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

    /*
       Input part
       */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _playerCharacter->move(-1, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _playerCharacter->move(1, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _playerCharacter->move(0, -1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _playerCharacter->move(0, 1);
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

    _window.display();

}
