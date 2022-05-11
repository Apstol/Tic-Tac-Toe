#pragma once

#include "Mark.hpp"
#include "Board.hpp"

class GenericPlayer
{
	public:
	        GenericPlayer(Mark::Type mark);
		virtual ~GenericPlayer();
		
		virtual bool makeMove(Board& board) = 0;
		
		Mark::Type mark() const;

	protected:
		Mark::Type _mark;
};
