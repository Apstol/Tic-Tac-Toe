#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "AIDifficultyStrategy.hpp"
#include <array>

class Game
{
    public:
	Game();
	~Game();

	void run();
	void changeGameState(GameState::State gameState);
	void setDifficulty(AIDifficultyStrategy::Difficulty difficulty);
	sf::Font& font();
	sf::Texture& boardTexture();
	sf::Texture& marksTexture();
	sf::RenderWindow& window();
	AIDifficultyStrategy::Difficulty difficulty() const;
	void setIsHumanWinner(bool isHumanWinner);
	bool isHumanWinner() const;
	void setIsTie(bool isTie);
	bool isTie() const;
	void setIsGameOver(bool isGameOver);
	bool isGameOver() const;

    private:
   	void _processEvents();
	void _update(sf::Time deltaTime);
	void _render();
	void _updateFramerateCount(sf::Time deltaTime);

	static const unsigned int _FramesPerSecond;

	sf::Color _backgroundClearColor;
	sf::RenderWindow _window;
	sf::Font _font;
	sf::Texture _boardTexture;
	sf::Texture _marksTexture;
	std::uint32_t _framesCount;
	sf::Text _framesCountText;
	sf::Time _framerateUpdateTime;
	bool _showFramerate;
	GameState* _currentState;
	AIDifficultyStrategy::Difficulty _difficulty;
	bool _isHumanWinner;
	bool _isTie;
	bool _isGameOver;
};
