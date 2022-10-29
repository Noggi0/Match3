/**
 * Match 3 game, by Vincent Son
 */

#ifndef __DRAWABLE_HPP__
#define __DRAWABLE_HPP__

#include <memory>
#include <SFML/Graphics.hpp>

class Drawable
{
	public:
		Drawable() = default;
		~Drawable() = default;
	protected:
		std::unique_ptr<sf::Sprite> sprite;
		std::unique_ptr<sf::Texture> texture;
};

#endif /* __DRAWABLE_HPP__ */