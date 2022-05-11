#include "GenericPlayer.hpp"
#include <iostream>

GenericPlayer::GenericPlayer(Mark::Type mark)
    : _mark{ mark }
{
}

GenericPlayer::~GenericPlayer() 
{
	//std::cout << "GenericPlayer destructor called" << std::endl;
}

Mark::Type GenericPlayer::mark() const
{
	return _mark;
}
