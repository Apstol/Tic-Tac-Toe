#include "Mark.hpp"
#include <iostream>
#include "Utilities.cpp"

Mark::Mark(sf::Texture& marksTexture, Mark::Type type, sf::Vector2f position)
	: _type{ type }
{
	_markSprite.setTexture(marksTexture);
	_setTextureRectByMarkType();
	_markSprite.setPosition(position);
}

Mark::~Mark()
{
	//std::cout << "Deleted Mark" << std::endl;
}

sf::Sprite Mark::sprite() const
{
	return _markSprite;
}

Mark::Type Mark::type() const
{
	return _type;
}

void Mark::setType(Mark::Type markType)
{
	_type = markType;
	_setTextureRectByMarkType();
}

void Mark::_setTextureRectByMarkType()
{
	if (_type == X)
	{
		_markSprite.setTextureRect(sf::IntRect(0, 0, 119, 130));
	}
	else if (_type == O)
	{
		_markSprite.setTextureRect(sf::IntRect(132, 0, 132, 130));
	}
	else if (_type == Empty)
	{
		_markSprite.setTextureRect(sf::IntRect(264, 0, 132, 130));
	}

	centerOrigin(_markSprite);
}

bool Mark::contains(const sf::Vector2i& point) const
{
	return _markSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(point));
}

void Mark::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(_markSprite, states);
}
