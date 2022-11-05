/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/Piece.hpp"
#include "../includes/Defines.hpp"
#include <iostream>

Piece::Piece(int type, std::pair<int, int> position)
	: mType(type)
{
	mPosition = std::move(position);
	std::string pathToAsset = ASSETS_PATH + "/" + std::to_string(type + 1) + ".png";

	mTexture = std::make_unique<sf::Texture>();
	if (!mTexture->loadFromFile(pathToAsset))
		std::cout << "------- Error loading asset -------" << std::endl;

	mSprite = std::make_unique<sf::Sprite>();
	mSprite->setTexture(*mTexture);
	mSprite->setScale(0.1f, 0.1f);
	mSprite->setPosition(mPosition.first, mPosition.second);
}

const int Piece::getType() const
{
	return mType;
}

const sf::Sprite* Piece::getSprite() const
{
	return mSprite.get();
}

const sf::Vector2f Piece::getPosition() const
{
	return mSprite->getPosition();
}

void Piece::setStatus(PieceState state)
{
	mState = state;

	if (mState == PieceState::SELECTED)
		mSprite->setScale(sf::Vector2f(0.11f, 0.11f));
	else
		mSprite->setScale(sf::Vector2f(0.1f, 0.1f));
}

const PieceState Piece::getStatus() const
{
	return mState;
}

const bool Piece::isSelected() const
{
	return mState == PieceState::SELECTED;
}

void Piece::setPosition(sf::Vector2f pos)
{
	mSprite->setPosition(pos);
	mPosition = std::make_pair(pos.x, pos.y);
}

void Piece::update()
{
	if (mState != PieceState::SWAPPING)
		return;

	if (static_cast<int>(this->getPosition().x) != mTargetPosition.x || static_cast<int>(this->getPosition().y) != mTargetPosition.y)
	{
		if (this->getPosition().x < mTargetPosition.x)
			mSprite->move(1, 0);
		else if (this->getPosition().x > mTargetPosition.x)
			mSprite->move(-1, 0);
		if (this->getPosition().y < mTargetPosition.y)
			mSprite->move(0, 1);
		else if (this->getPosition().y > mTargetPosition.y)
			mSprite->move(0, -1);
	}
	else
	{
		mState = PieceState::NONE;
		mTargetPosition = {-1, -1};
	}
}

void Piece::setTargetPosition(sf::Vector2f pos)
{
	mTargetPosition = pos;
}

const sf::Vector2f Piece::getTargetPosition() const
{
	return mTargetPosition;
}