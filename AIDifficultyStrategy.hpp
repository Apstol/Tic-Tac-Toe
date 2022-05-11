#pragma once

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include <iostream>

class AIDifficultyStrategy
{
	public:
		virtual ~AIDifficultyStrategy();

		enum Difficulty
		{
			Easy,
			Unbeatable
		};

		virtual int chooseBestMove(Board& board) = 0;
};
