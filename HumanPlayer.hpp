#pragma once

#include "GenericPlayer.hpp"

class HumanPlayer : public GenericPlayer
{
	public:
		HumanPlayer(const sf::RenderWindow& window, Mark::Type mark);
		~HumanPlayer();

		virtual bool makeMove(Board& board);

	private:
		const sf::RenderWindow& _window;
};
