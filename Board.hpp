#pragma once

#include <SFML/Graphics.hpp>
#include "Mark.hpp"
#include <array>

typedef std::array<Mark*, 9> BoardDataType;

class Board : public sf::Transformable, public sf::Drawable
{
	public:
		Board(sf::Texture& boardTexture, sf::Texture& marksTexture);
		~Board();

		BoardDataType& boardData();
		bool setMarkByPosition(const sf::Vector2i& position, Mark::Type markType);
		void setMarkByIndex(int index, Mark::Type markType);
		bool isMatch(Mark::Type mark);
		bool isTie() const;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void _initBoardData(sf::Texture& marksTexture);

		sf::Sprite _boardSprite;
		sf::Sprite _xMarkSprite;
		sf::Sprite _yMarkSprite;
		BoardDataType _boardData;
};
