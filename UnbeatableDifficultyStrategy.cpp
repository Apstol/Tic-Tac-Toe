#include "UnbeatableDifficultyStrategy.hpp"
#include <iostream>
#include <algorithm>
#include <utility>
#include <iterator>

UnbeatableDifficultyStrategy::UnbeatableDifficultyStrategy(Mark::Type aiMark)
	: _aiMark{ aiMark }
{
}

UnbeatableDifficultyStrategy::~UnbeatableDifficultyStrategy()
{
	//std::cout << "Deleted UnbeatableDifficultyStrategy" << std::endl;
}

// Uses minimax algorithm to calculate the best move
int UnbeatableDifficultyStrategy::chooseBestMove(Board& board)
{
	IndexToScoreListType indexToScoreList;
	indexToScoreList.reserve(9);

	_fillIndexToScoreList(indexToScoreList, board.boardData());

	for (int i{ 0 }; i < indexToScoreList.size(); ++i)
	{
		board.setMarkByIndex(indexToScoreList[i].first, _aiMark);
		indexToScoreList[i].second = _minimax(board, true);
		board.setMarkByIndex(indexToScoreList[i].first, Mark::Type::Empty);
	}

	IndexToScoreListType::const_iterator result{ std::max_element(indexToScoreList.begin(), indexToScoreList.end(), [](auto a, auto b){ return a.second < b.second; }) };

	return result->first;
}

int UnbeatableDifficultyStrategy::_minimax(Board& board, bool isMaximizer)
{
	Mark::Type humanPlayerMark = _aiMark == Mark::Type::X
		? Mark::Type::O
		: Mark::Type::X;

	Mark::Type currentMark = isMaximizer 
		? _aiMark
		: humanPlayerMark;

	if (isMaximizer && board.isMatch(currentMark))
	{
		return 10;
	}
	else if (!isMaximizer && board.isMatch(currentMark))
	{
		return -10;
	}

	IndexToScoreListType indexToScoreList;
	indexToScoreList.reserve(9);

	_fillIndexToScoreList(indexToScoreList, board.boardData());

	// if it's a tie
	if (indexToScoreList.size() == 0)
	{
	    return 0;
	}

	Mark::Type nextMark = currentMark == Mark::Type::X 
		? Mark::Type::O
		: Mark::Type::X;

	for (int i{ 0 }; i < indexToScoreList.size(); ++i)
	{
		board.setMarkByIndex(indexToScoreList[i].first, nextMark);
		indexToScoreList[i].second = _minimax(board, !isMaximizer);
		board.setMarkByIndex(indexToScoreList[i].first, Mark::Type::Empty);
	}

	IndexToScoreListType::const_iterator result;

	isMaximizer = !isMaximizer;

	if (isMaximizer)
	{
		result = std::max_element(indexToScoreList.begin(), indexToScoreList.end(), [](auto a, auto b){ return (a.second < b.second); });
	}
	else
	{
		result = std::min_element(indexToScoreList.begin(), indexToScoreList.end(), [](auto a, auto b){ return (a.second < b.second); });
	}

	return result->second;
}

void UnbeatableDifficultyStrategy::_fillIndexToScoreList(IndexToScoreListType& indexToScoreList, BoardDataType& boardData)
{
	for (int i{ 0 }; i < boardData.size(); ++i)
	{
		if (boardData[i]->type() == Mark::Type::Empty)
		{
			indexToScoreList.emplace_back(i, 0);
		}
	}
}

