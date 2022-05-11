#pragma once

#include "AIDifficultyStrategy.hpp"
#include <random>

class EasyDifficultyStrategy : public AIDifficultyStrategy
{
	public:
		EasyDifficultyStrategy();
		~EasyDifficultyStrategy();

		virtual int chooseBestMove(Board& board) override;
	
	private:
		std::mt19937 _rng;
};
