#include "GameState.hpp"
#include "Game.hpp"
#include "EasyDifficultyStrategy.hpp"
#include "UnbeatableDifficultyStrategy.hpp"
#include <iostream>
#include <ctime>
#include <string>
#include "Utilities.cpp"
#include "Mark.hpp"

GameState::GameState(Game* const game)
    : _game{ game }
{
}

GameState::~GameState()
{
}

MenuState::MenuState(Game* const game)
    : GameState(game), _chosenDifficulty{ false }
{
    _chooseEasyDifficultyLevelText.setFont(game->font());
    _chooseEasyDifficultyLevelText.setCharacterSize(28);
    _chooseEasyDifficultyLevelText.setString("Press 'e' to play against easy opponent");
    _chooseEasyDifficultyLevelText.setFillColor(sf::Color(0, 0, 0, 255));
    centerOrigin(_chooseEasyDifficultyLevelText);
    _chooseEasyDifficultyLevelText.setPosition(240, 120);

    _chooseUnbeatableDifficultyLevelText.setFont(game->font());
    _chooseUnbeatableDifficultyLevelText.setCharacterSize(28);
    _chooseUnbeatableDifficultyLevelText.setString("Or press 'u' to play against unbeatable opponent");
    _chooseUnbeatableDifficultyLevelText.setFillColor(sf::Color(0, 0, 0, 255));
    centerOrigin(_chooseUnbeatableDifficultyLevelText);
    _chooseUnbeatableDifficultyLevelText.setPosition(240, 240);
}

MenuState::~MenuState()
{
    //std::cout << "MenuState destructor called" << std::endl;
}

void MenuState::processEvents(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::E)
		{
			_game->setDifficulty(AIDifficultyStrategy::Easy);
			_chosenDifficulty = true;
		}
		else if (event.key.code == sf::Keyboard::U)
		{
			_game->setDifficulty(AIDifficultyStrategy::Unbeatable);
			_chosenDifficulty = true;
		}
	}
}

void MenuState::update()
{
	if (_chosenDifficulty)
	{
		_game->changeGameState(GameState::Playing);
	}
}

void MenuState::render()
{
    _game->window().draw(_chooseEasyDifficultyLevelText);
    _game->window().draw(_chooseUnbeatableDifficultyLevelText);
}

PlayingState::PlayingState(Game* const game)
    : GameState(game), _isHumanTurn{ true}, _humanPlayed{ false }
{
	Mark::Type humanMark{ Mark::Type::X };
	Mark::Type aiMark{ Mark::Type::O };

	_humanPlayer = new HumanPlayer(game->window(), humanMark);

	AIDifficultyStrategy* aiDifficultyStrategy{ _aiDifficultyStrategyFromDifficulty(game->difficulty(), aiMark) };
	_aiPlayer = new AIPlayer(aiDifficultyStrategy, aiMark);

	_board = new Board(game->boardTexture(), game->marksTexture());
}

PlayingState::~PlayingState()
{
	delete _humanPlayer;
	delete _aiPlayer;
	delete _board;
	//std::cout << "PlayingState destructor called" << std::endl;
}

AIDifficultyStrategy* PlayingState::_aiDifficultyStrategyFromDifficulty(AIDifficultyStrategy::Difficulty difficulty, Mark::Type aiMark)
{
	switch (difficulty)
	{
		case AIDifficultyStrategy::Easy:
			return new EasyDifficultyStrategy();
			break;
		case AIDifficultyStrategy::Unbeatable:
			return new UnbeatableDifficultyStrategy(aiMark);
			break;
	}
	return new EasyDifficultyStrategy();
}

void PlayingState::_changeTurn()
{
	_isHumanTurn = !_isHumanTurn;
}

void PlayingState::processEvents(sf::Event& event)
{
	if (_isHumanTurn && event.type == sf::Event::MouseButtonPressed)
	{
		if (_humanPlayer->makeMove(*_board))
		{
		    _humanPlayed = true;
		}
	}
}

void PlayingState::update()
{
        if (_game->isGameOver())
	{
	    sf::sleep(sf::seconds(2));
	    _game->changeGameState(GameState::GameOver);
	    return;
	}

	Mark::Type mark;

	if (_isHumanTurn)
	{
		if (!_humanPlayed)
		{
			return;
		}

		_humanPlayed = false;
		mark = _humanPlayer->mark();
	}
	else
	{
		_aiPlayer->makeMove(*_board);
		mark = _aiPlayer->mark();
		sf::sleep(sf::seconds(1));
	}

	if (_board->isMatch(mark))
	{
		if (_isHumanTurn)
		{
		    _game->setIsHumanWinner(true);
		}
		else
		{
		    _game->setIsHumanWinner(false);
		}

		_game->setIsGameOver(true);
		return;
	}
	else if (_board->isTie())
	{
	    _game->setIsTie(true);
	    _game->setIsGameOver(true);
	    return;
	}

	_changeTurn();
}

void PlayingState::render()
{
	_game->window().draw(*_board);

	for (Mark* mark : _board->boardData())
	{
		if (mark)
		{
			_game->window().draw(*mark);
		}
	}
}

GameOverState::GameOverState(Game* const game)
    : GameState(game)
{
    std::string text{};

    if (_game->isTie())
    {
	text = "It's a tie!";
    }
    else if (_game->isHumanWinner())
    {
	text = "You won!";
    }
    else
    {
	text = "You lost!";
    }

    _gameOverText.setFont(_game->font());
    _gameOverText.setCharacterSize(60);
    _gameOverText.setString(text);
    _gameOverText.setFillColor(sf::Color(0, 0, 0, 255));
    centerOrigin(_gameOverText);
    _gameOverText.setPosition(240, 240);
}

GameOverState::~GameOverState()
{
    //std::cout << "GameOverState destructor called" << std::endl;
}

void GameOverState::processEvents(sf::Event& event)
{
}

void GameOverState::update()
{
}

void GameOverState::render()
{
        _game->window().draw(_gameOverText);
}
