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
	this->sprite->setPosition(this->position.first, this->position.second);
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

void Piece::setStatus(PieceState state)
{
	this->state = state;

	if (this->state == PieceState::SELECTED)
		this->sprite->setScale(sf::Vector2f(0.11f, 0.11f));
	else
		this->sprite->setScale(sf::Vector2f(0.1f, 0.1f));
}

const PieceState Piece::getStatus() const
{
	return this->state;
}

const bool Piece::isSelected() const
{
	return this->state == PieceState::SELECTED;
}

void Piece::setPosition(sf::Vector2f pos)
{
	this->sprite->setPosition(pos);
	this->position = std::make_pair(pos.x, pos.y);
}

void Piece::update()
{
	if (this->state != PieceState::SWAPPING)
		return;

	if (static_cast<int>(this->getPosition().x) != this->targetPosition.x || static_cast<int>(this->getPosition().y) != this->targetPosition.y)
	{
		if (this->getPosition().x < this->targetPosition.x)
			this->sprite->move(1, 0);
		else if (this->getPosition().x > this->targetPosition.x)
			this->sprite->move(-1, 0);
		if (this->getPosition().y < this->targetPosition.y)
			this->sprite->move(0, 1);
		else if (this->getPosition().y > this->targetPosition.y)
			this->sprite->move(0, -1);
	}
	else
	{
		this->state = PieceState::NONE;
		this->targetPosition = {-1, -1};
	}
}

void Piece::setTargetPosition(sf::Vector2f pos)
{
	this->targetPosition = pos;
}

const sf::Vector2f Piece::getTargetPosition() const
{
	return this->targetPosition;
}