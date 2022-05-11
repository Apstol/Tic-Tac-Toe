#include "EasyDifficultyStrategy.hpp"
#include <iostream>
#include <algorithm>

EasyDifficultyStrategy::EasyDifficultyStrategy()
{
	_rng.seed(static_cast<std::mt19937::result_type>(std::time(nullptr)));
}

EasyDifficultyStrategy::~EasyDifficultyStrategy()
{
	//std::cout << "EasyDifficultyStrategy destructor called" << std::endl;
}

// Chooses a random move
int EasyDifficultyStrategy::chooseBestMove(Board& board)
{
	std::vector<int> indices;

	for (int i{ 0 }; i < board.boardData().size(); ++i)
	{
		if (board.boardData()[i]->type() == Mark::Type::Empty)
		{
			indices.push_back(i);
		}
	}

	std::shuffle(std::begin(indices), std::end(indices), _rng);

	return indices.front();
}
