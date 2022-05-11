#include <SFML/Graphics.hpp>

template <typename T> 
void centerOrigin(T& t)
{
	sf::FloatRect bounds{ t.getLocalBounds() };
	t.setOrigin(bounds.width / 2, bounds.height / 2);
}
