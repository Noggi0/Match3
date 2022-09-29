/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/Piece.hpp"
#include "../includes/Defines.hpp"
#include <iostream>

Piece::Piece(int type, std::pair<int, int> position)
	: type(std::move(type))
{
	this->position = std::move(position);
	std::string pathToAsset = ASSETS_PATH + "/" + std::to_string(type + 1) + ".png";

	this->texture = std::make_unique<sf::Texture>();
	if (!this->texture->loadFromFile(pathToAsset))
		std::cout << "------- Error loading asset -------" << std::endl;

	this->sprite = std::make_unique<sf::Sprite>();
	this->sprite->setTexture(*this->texture);
	this->sprite->setScale(0.1f, 0.1f);
	this->sprite->setPosition(this->position.first * 60, this->position.second * 60);
	std::cout << "------- Piece created -------" << std::endl;
}

const int Piece::getType() const
{
	return this->type;
}

const sf::Sprite* Piece::getSprite() const
{
	return this->sprite.get();
}

const sf::Vector2f Piece::getPosition() const
{
	return this->sprite->getPosition();
}

void Piece::setSelected(bool selected)
{
	this->selected = selected;

	if (this->selected)
		this->sprite->setScale(sf::Vector2f(0.11f, 0.11f));
	else if (!this->selected)
		this->sprite->setScale(sf::Vector2f(0.1f, 0.1f));
}

const bool Piece::isSelected() const
{
	return this->selected;
}

void Piece::setPosition(sf::Vector2f pos)
{
	this->sprite->setPosition(pos);
	this->position = std::make_pair(pos.x, pos.y);
}