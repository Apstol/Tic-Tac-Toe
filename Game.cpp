#include "Game.hpp"
#include "GameState.hpp"
#include <string>

const unsigned int Game::_FramesPerSecond{ 60 };

Game::Game() 
    : _window{ sf::VideoMode(480, 480), "Tic-Tac-Toe" },
    _font{ },
    _framesCount{ 0 },
    _framesCountText{ },
    _framerateUpdateTime{ },
    _showFramerate{ false },
    _backgroundClearColor{ 255, 255, 255, 0 },
    _currentState{ nullptr },
    _isHumanWinner{ false },
    _isTie{ false },
    _isGameOver{ false }
{
   _window.setFramerateLimit(_FramesPerSecond); 

   _font.loadFromFile("assets/Lemon Fresh.otf");
   _boardTexture.loadFromFile("assets/board.png");
   _marksTexture.loadFromFile("assets/marks.png");

   _framesCountText.setFont(_font);
   _framesCountText.setCharacterSize(16);
   _framesCountText.setFillColor(sf::Color(0, 0, 0, 255));
   _framesCountText.setPosition(sf::Vector2f(5.f, 5.f));

    changeGameState(GameState::Menu);
}

Game::~Game()
{
	delete _currentState;
}

void Game::run()
{
    sf::Clock clock;
    sf::Time deltaTime{ sf::Time::Zero };
    while (_window.isOpen())
    {
	deltaTime = clock.restart();

	_processEvents();
	_update(deltaTime);
	_render();
    }
}

sf::Texture& Game::boardTexture()
{
	return _boardTexture;
}

sf::Texture& Game::marksTexture()
{
	return _marksTexture;
}

void Game::setDifficulty(AIDifficultyStrategy::Difficulty difficulty)
{
	_difficulty = difficulty;
}

AIDifficultyStrategy::Difficulty Game::difficulty() const
{
	return _difficulty;
}

void Game::setIsHumanWinner(bool isHumanWinner)
{
    _isHumanWinner = isHumanWinner;
}

bool Game::isHumanWinner() const
{
    return _isHumanWinner;
}

bool Game::isTie() const
{
    return _isTie;
}

void Game::setIsTie(bool isTie)
{
    _isTie = isTie;
}

void Game::setIsGameOver(bool isGameOver)
{
    _isGameOver = isGameOver;
}

bool Game::isGameOver() const
{
    return _isGameOver;
}

void Game::changeGameState(GameState::State gameState)
{
	delete _currentState;

	switch(gameState)
	{
		case GameState::Menu:
			_currentState = new MenuState(this);
			break;
		case GameState::Playing:
			_currentState = new PlayingState(this);
			break;
		case GameState::GameOver:
			_currentState = new GameOverState(this);
			break;
	}
}

sf::Font& Game::font()
{
    return _font;
}

sf::RenderWindow& Game::window()
{
    return _window;
}

void Game::_processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
	if (event.type == sf::Event::Closed)
	{
	    _window.close();
	}

	if (event.type == sf::Event::KeyPressed)
	{
	    if (event.key.code == sf::Keyboard::F)
	    {
		_showFramerate = !_showFramerate;
	    }
	}

	_currentState->processEvents(event);
    }
}

void Game::_update(sf::Time deltaTime)
{
    _currentState->update();
    _updateFramerateCount(deltaTime);
}

void Game::_render()
{
    _window.clear(_backgroundClearColor);

    if (_showFramerate)
    {
	_window.draw(_framesCountText);
    }

    _currentState->render();

    _window.display();
}

void Game::_updateFramerateCount(sf::Time deltaTime)
{
    _framesCount++;
    _framerateUpdateTime += deltaTime;
    if (_framerateUpdateTime >= sf::seconds(1.f))
    {
	_framesCountText.setString("FPS: " + std::to_string(_framesCount));
	_framesCount = 0;
	_framerateUpdateTime -= sf::seconds(1.f);
    }
}
