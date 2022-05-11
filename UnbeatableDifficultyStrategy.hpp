#pragma once

#include "AIDifficultyStrategy.hpp"
#include "AIPlayer.hpp"
#include "Board.hpp"

typedef std::vector<std::pair<int, int>> IndexToScoreListType;

class UnbeatableDifficultyStrategy : public AIDifficultyStrategy
{
	public:
		UnbeatableDifficultyStrategy(Mark::Type aiMark);
		~UnbeatableDifficultyStrategy();

		int chooseBestMove(Board& board) override;

	private:
		int _minimax(Board& board, bool isMaximizer);
		void _fillIndexToScoreList(IndexToScoreListType& indexToScoreList, BoardDataType& boardData);
		Mark::Type _aiMark;
};
