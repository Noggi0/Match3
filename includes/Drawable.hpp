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
		virtual bool loadSprite(const std::string &filename);
		virtual void setPosition(int x, int y);
		virtual void setScale(float x, float y);
		virtual void setRotation(float angle);
		virtual const sf::Sprite* getSprite() const;
		sf::Vector2f targetScale = {1.0f, 1.0f};
		~Drawable() = default;
	protected:
		std::unique_ptr<sf::Sprite> mSprite;
		std::unique_ptr<sf::Texture> mTexture;
};

#endif /* __DRAWABLE_HPP__ */