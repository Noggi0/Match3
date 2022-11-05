/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/Drawable.hpp"

void Drawable::setScale(float x, float y)
{
	mSprite->setScale(sf::Vector2f(x, y));
}

void Drawable::setPosition(int x, int y)
{
	mSprite->setPosition(sf::Vector2f(x, y));
}

bool Drawable::loadSprite(const std::string &filename)
{
	mTexture = std::make_unique<sf::Texture>();
	if (!mTexture->loadFromFile(filename))
		return false;

	mSprite = std::make_unique<sf::Sprite>();
	mSprite->setTexture(*mTexture);
	return true;
}

const sf::Sprite* Drawable::getSprite() const
{
	return mSprite.get();
}