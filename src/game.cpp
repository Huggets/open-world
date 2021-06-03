#include "game.hpp"
#include <ctime>
#include <chrono>
#include <queue>
#include <fstream>
#include <thread>
#include "console.hpp"
#include "worldfileparser.hpp"

Game::Game(
        const std::string& worldFilename,
        float playerX,
        float playerY
        ) :
    _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Open World", sf::Style::Close),
    _font(),
    _playerCoordinatesText(),
    _fpsText(),
    _textures(),
    _world(nullptr),
    _startTime(clock()),
    _lastTime(_startTime),
    _diffTime(0),
    _fpsTime(0),
    _fpsTimeTmp(0),
    _sleepTime(0),
    _person1(),
    _person2(),
    _playerCharacter(&_person1),
    _scrollX(0),
    _scrollY(0)
{
    /*
       Loading files
     */

    // FONTS
    _font.loadFromFile("data/fonts/linbiolum.otf");

    // WORLDS
    // Generating the world
    _world = wfp::parse(worldFilename, _textures);

    // TEXTURES
    for (auto p : _textures)
    {
        _textures[p.first].loadFromFile("data/images/" + p.first + ".png");
    }
    _textures["person"] = sf::Texture();
    _textures["person"].loadFromFile("data/images/person-top.png");

    /*
       Default settings
     */
    _person1.setTexture(_textures["person"]);
    _person2.setTexture(_textures["person"]);
    _person1.setPosition(playerX, playerY);
    _person2.setPosition(playerX, playerY);
    _playerCoordinatesText.setFont(_font);
    _playerCoordinatesText.setPosition(0, 570);
    _playerCoordinatesText.setFillColor(sf::Color::Black);
    _fpsText.setFont(_font);
    _fpsText.setPosition(0, 0);
    _fpsText.setFillColor(sf::Color::Black);
    _fpsText.setString("No fps");
    _rectangleLimitScroll.x = WINDOW_WIDTH / 2;
    _rectangleLimitScroll.y = WINDOW_HEIGHT / 2;
    _rectangleLimitScroll.width = 1;
    _rectangleLimitScroll.height = 1;
    _maxScrollX = _world->getWidth() * WORLDPIECE_SIZE * TILE_SIZE - WINDOW_WIDTH;
    _maxScrollY = _world->getHeight() * WORLDPIECE_SIZE * TILE_SIZE - WINDOW_HEIGHT;
}

void Game::run(bool profile, const std::string& performanceFile)
{
    // Each time we save the fps we add it in fpsTotal
    unsigned long int fpsTotal(0);
    // Number of fps saved
    unsigned int fpsTotalCount(0);
    // We will store the information about the performance in a file
    std::fstream profileFile(
            performanceFile,
            std::fstream::in | std::fstream::app);
    // Contains all the fps saved
    std::queue<int> fps;

    // Run the game and save the performance profile
    if (profile and profileFile.is_open())
    {
        console::info(
                "Performance information will be saved in the file "
                + performanceFile);

        while (_window.isOpen())
        {
            _frame();

            // We save the fps each half second
            _fpsTimeTmp = (float) _startTime/ CLOCKS_PER_SEC * 2;
            if (_fpsTimeTmp > _fpsTime)
            {
                _fpsTime = _fpsTimeTmp;
                int n =
                    1 / ((float) (_startTime - _lastTime) / CLOCKS_PER_SEC
                        );
                fps.push(n);
                fpsTotalCount++;
                fpsTotal += n;
                _fpsText.setString(std::to_string(n));
            }
        } 

        // Writing all fps and fps average into the profile file
        profileFile.put('\n');
        while (!fps.empty())
        {
            profileFile << fps.front() << ' ';
            fps.pop();
        }
        if (fpsTotalCount == 0)
        {
            profileFile << "Average: " << 0;
        }
        else
        {
            profileFile << "Average: " << fpsTotal / fpsTotalCount;
        }
        profileFile.close();
    }
    // Run the game normally
    else
    {
        while (_window.isOpen())
        {
            _frame();
        }
    }
}

// As this function is executed each frame, we need to have the best
// performance. So we inline it to avoid a function call
inline void Game::_frame()
{
    _lastTime = _startTime;
    _startTime = clock();
    _diffTime = _startTime-_lastTime;

    // Handle the window events
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _window.close();
        }
    }

    /*
       INPUT PART
     */
    moveSpeed = 150*(float) ((float)(_diffTime + _sleepTime) / (float)CLOCKS_PER_SEC);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        // The user now controls _person1
        _playerCharacter = &_person1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        // The user now controls _person2
        _playerCharacter = &_person2;
    }

    _tmpPlayerX = _playerCharacter->getX();
    _tmpPlayerY = _playerCharacter->getY();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _tmpPlayerX -= moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        _tmpPlayerX += moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        _tmpPlayerY += moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        _tmpPlayerY -= moveSpeed;
    }

    /*
       MAIN PART
     */
    // Displaying texts
    _playerCoordinatesText.setString(
            "X: " + std::to_string(_playerCharacter->getX()) +
            ", Y: " + std::to_string(_playerCharacter->getY()) +
            ", scrollX: " + std::to_string(_scrollX) +
            ", scrollY: " + std::to_string(_scrollY)
            );
    _fpsText.setString(std::to_string(
                (int) ( 1 / (float) ((float)(_diffTime + _sleepTime) / (float)CLOCKS_PER_SEC) )
                ));
    // Moving the player
    Character testCharacter(*_playerCharacter);
    testCharacter.setPosition(_tmpPlayerX, _tmpPlayerY);
    if (_world->collide(testCharacter))
    {
        _tmpPlayerX = _playerCharacter->getX();
        _tmpPlayerY = _playerCharacter->getY();
    }
    _playerCharacter->setPosition(_tmpPlayerX, _tmpPlayerY);

    // Updating the scrolling
    _xLimMin = _scrollX + _rectangleLimitScroll.x;
    _yLimMin = _scrollY + _rectangleLimitScroll.y;
    _xLimMax = _xLimMin + _rectangleLimitScroll.width;
    _yLimMax = _yLimMin + _rectangleLimitScroll.height;
    if (_playerCharacter->getX() < _xLimMin)
    {
        _scrollX -= _xLimMin - _playerCharacter->getX();
    }
    else if (_playerCharacter->getX() > _xLimMax)
    {
        _scrollX += _playerCharacter->getX() - _xLimMax;
    }
    if (_playerCharacter->getY() < _yLimMin)
    {
        _scrollY -= _yLimMin - _playerCharacter->getY();
    }
    else if (_playerCharacter->getY() > _yLimMax)
    {
        _scrollY += _playerCharacter->getY() - _yLimMax;
    }
    if (_scrollX < 0)
    {
        _scrollX = 0;
    }
    else if (_scrollX > _maxScrollX)
    {
        _scrollX = _maxScrollX;
    }
    if (_scrollY < 0)
    {
        _scrollY = 0;
    }
    else if (_scrollY > _maxScrollY)
    {
        _scrollY = _maxScrollY;
    }


    // Updating the coordinates' characters
    _person1.scroll(_scrollX, _scrollY);
    _person2.scroll(_scrollX, _scrollY);
    _person1.updatePosition();
    _person2.updatePosition();

    /*
       DRAWING PART
     */
    _window.clear(sf::Color::White);

    _world->draw(_window, _scrollX, _scrollY);
    _person1.draw(_window);
    _person2.draw(_window);
    _window.draw(_playerCoordinatesText);
    _window.draw(_fpsText);

    _window.display();

    /*
       SLEEP A CERTAIN AMOUNT OF TIME IN ORDER TO HAVE A FPS LIMIT
     */
    _sleepTime = int (1.f / 144 * CLOCKS_PER_SEC - _diffTime);
    std::this_thread::sleep_for(
            std::chrono::duration<int, std::ratio<1, CLOCKS_PER_SEC>>(_sleepTime)
            );
}
