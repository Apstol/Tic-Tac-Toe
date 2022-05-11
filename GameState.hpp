#pragma once

#include <SFML/Graphics.hpp>
#include "HumanPlayer.hpp"
#include "AIPlayer.hpp"
#include "Board.hpp"

class Game;

class GameState
{
    public:
	GameState(Game* const game);
	virtual ~GameState();

	enum State {
	    Menu,
	    Playing,
	    GameOver,

	    Count
	};

	virtual void processEvents(sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

    protected:
	void _centerOrigin(sf::Text& text);

	Game* const _game;
};

class MenuState : public GameState
{
    public:
	MenuState(Game* const game);
	~MenuState();

	void processEvents(sf::Event& event);
	void update();
	void render();
	
    private:
	sf::Text _chooseEasyDifficultyLevelText;
	sf::Text _chooseUnbeatableDifficultyLevelText;
	bool _chosenDifficulty;
};

class PlayingState : public GameState
{
    public:
	PlayingState(Game* const game);
	~PlayingState();

	void processEvents(sf::Event& event);
	void update();
	void render();

    private:
	    AIDifficultyStrategy* _aiDifficultyStrategyFromDifficulty(AIDifficultyStrategy::Difficulty difficulty, Mark::Type aiMark);
	    void _changeTurn();
	    bool _isMatch(Mark::Type mark);
	    
	    bool _isHumanTurn;
	    bool _humanPlayed;
	    HumanPlayer* _humanPlayer;
	    AIPlayer* _aiPlayer;
	    Board* _board;
};

class GameOverState : public GameState
{
    public:
	GameOverState(Game* const game);
	~GameOverState();

	void processEvents(sf::Event& event);
	void update();
	void render();

    private:
	sf::Text _gameOverText;
};
