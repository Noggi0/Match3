/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/Drawable.hpp"

void Drawable::setScale(float x, float y)
{
	this->sprite->setScale(sf::Vector2f(x, y));
}

void Drawable::setPosition(int x, int y)
{
	this->sprite->setPosition(sf::Vector2f(x, y));
}

bool Drawable::loadSprite(std::string filename)
{
	this->texture = std::make_unique<sf::Texture>();
	if (!this->texture->loadFromFile(filename))
		return false;

	this->sprite = std::make_unique<sf::Sprite>();
	this->sprite->setTexture(*this->texture);
}

const sf::Sprite* Drawable::getSprite() const
{
	return this->sprite.get();
}