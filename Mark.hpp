#pragma once

#include <SFML/Graphics.hpp>

class Mark : public sf::Transformable, public sf::Drawable
{
	public:
		enum Type
		{
			X,
			O,
			Empty,

			Count
		};

		Mark(sf::Texture& marksTexture, Mark::Type type, sf::Vector2f position);
		~Mark();

		Mark::Type type() const;

		void setType(Mark::Type markType);

		bool contains(const sf::Vector2i& point) const;

		sf::Sprite sprite() const;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void _setTextureRectByMarkType();

		Type _type;
		sf::Sprite _markSprite;
};
