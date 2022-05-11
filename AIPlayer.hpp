#pragma once

#include "GenericPlayer.hpp"
#include "AIDifficultyStrategy.hpp"

class AIPlayer : public GenericPlayer
{
	public:
		AIPlayer(AIDifficultyStrategy* behaviorStrategy, Mark::Type mark);
		~AIPlayer();

		virtual bool makeMove(Board& board);

	private:
		AIDifficultyStrategy* _behaviorStrategy;
};
