#include "HumanPlayer.hpp"
#include <iostream>

HumanPlayer::HumanPlayer(const sf::RenderWindow& window, Mark::Type mark)
	: GenericPlayer(mark), _window{ window }
{
}

HumanPlayer::~HumanPlayer()
{
	//std::cout << "HumanPlayer destructor called" << std::endl;
}

bool HumanPlayer::makeMove(Board& board)
{
	return board.setMarkByPosition(sf::Mouse::getPosition(_window), _mark);
}
