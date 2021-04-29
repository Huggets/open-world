#include <string>
#include <ctime>
#include "engine.hpp"
#include "console.hpp"
#include "worldfileparser.hpp"

#define PNG_PERSON "data/images/person.png"
#define FONT_LINBIOLUM "data/fonts/linbiolum.otf"
#define WORLD_CONFIG "data/worlds/world1.world"

Engine::Engine() :
    _window(sf::VideoMode(800, 600), "Open World", sf::Style::Close),
    _personTexture(),
    _font(),
    _playerCoordinatesText(),
    _fps(),
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
    if (!_personTexture.loadFromFile(PNG_PERSON)) {
        Console::warning(PNG_PERSON);
    }
    if (!_font.loadFromFile(FONT_LINBIOLUM)) {
        Console::warning(FONT_LINBIOLUM);
    }

    WorldFileParser::parse(WORLD_CONFIG);

    _person1.setTexture(_personTexture);
    _person2.setTexture(_personTexture);
    _playerCoordinatesText.setFont(_font);
    _playerCoordinatesText.setPosition(0, 570);
    _playerCoordinatesText.setFillColor(sf::Color::Black);
    _fps.setFont(_font);
    _fps.setFillColor(sf::Color::Black);
}

void Engine::frame() {
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
    // We don't want to update the fps at each frame but only each half second
    _fpsTimeTmp = (float) _startTime/(float) CLOCKS_PER_SEC * 2;
    if (_fpsTimeTmp > _fpsTime) {
        _fpsTime = _fpsTimeTmp;
        _fps.setString(std::to_string(
                    (int) (1 / ((float) (_startTime - _lastTime) / CLOCKS_PER_SEC))
                    ));
    }

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
    _window.draw(_fps);

    _window.display();

}

bool Engine::isWindowOpen() const {
    return _window.isOpen();
}
