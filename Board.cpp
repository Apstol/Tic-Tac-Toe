#include "Board.hpp"
#include "Mark.hpp"
#include <iostream>


Board::Board(sf::Texture& boardTexture, sf::Texture& marksTexture)
{
	_boardSprite.setTexture(boardTexture);
	_boardSprite.setPosition(0, 0);

	_initBoardData(marksTexture);
}

Board::~Board()
{
	//std::cout << "Board desctructor called" << std::endl;
	for (Mark* mark : _boardData)
	{
		delete mark;
	}
}

void Board::_initBoardData(sf::Texture& marksTexture)
{
	int xOffset{ 80 };
	int yOffset{ 80 };
	for (int i{ 0 }; i < _boardData.size(); ++i)
	{
		if (i != 0)
		{
			if (i % 3 == 0)
			{
				xOffset = 80;
				yOffset += 160;
			}
			else
			{
				xOffset += 160;
			}
		}

		_boardData[i] = new Mark(marksTexture, Mark::Type::Empty, sf::Vector2f(xOffset, yOffset));
	}
}

BoardDataType& Board::boardData()
{
	return _boardData;
}

bool Board::setMarkByPosition(const sf::Vector2i& position, Mark::Type markType)
{
	for (Mark* cell : _boardData)
	{
		if (cell->type() == Mark::Type::Empty
			&& cell->contains(position))
		{
			cell->setType(markType);
			return true;
		}	
	}

	return false;
}

void Board::setMarkByIndex(int index, Mark::Type markType)
{
	_boardData[index]->setType(markType);
}

bool Board::isMatch(Mark::Type mark)
{
	if (
		_boardData[0]->type() == mark && _boardData[1]->type() == mark && _boardData[2]->type() == mark
		|| _boardData[3]->type() == mark && _boardData[4]->type() == mark && _boardData[5]->type() == mark
		|| _boardData[6]->type() == mark && _boardData[7]->type() == mark && _boardData[8]->type() == mark
		|| _boardData[0]->type() == mark && _boardData[3]->type() == mark && _boardData[6]->type() == mark
		|| _boardData[1]->type() == mark && _boardData[4]->type() == mark && _boardData[7]->type() == mark
		|| _boardData[2]->type() == mark && _boardData[5]->type() == mark && _boardData[8]->type() == mark
		|| _boardData[0]->type() == mark && _boardData[4]->type() == mark && _boardData[8]->type() == mark
		|| _boardData[2]->type() == mark && _boardData[4]->type() == mark && _boardData[6]->type() == mark
	)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::isTie() const
{
    for (const Mark* const mark : _boardData)
    {
	if (mark->type() == Mark::Type::Empty)
	{
	    return false;
	}
    }

    return true;
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(_boardSprite, states);
}
