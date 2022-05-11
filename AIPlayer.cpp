#include "AIPlayer.hpp"
#include <iostream>

AIPlayer::AIPlayer(AIDifficultyStrategy* behaviorStrategy, Mark::Type mark) 
    : GenericPlayer(mark), _behaviorStrategy{ behaviorStrategy }
{
}

AIPlayer::~AIPlayer()
{
	//std::cout << "Deleted AIPlayer" << std::endl;
	delete _behaviorStrategy;
}

bool AIPlayer::makeMove(Board& board)
{
	int index{ _behaviorStrategy->chooseBestMove(board) };
	board.setMarkByIndex(index, _mark);
	return true;
}
