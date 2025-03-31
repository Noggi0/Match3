/**
 * Match 3 game, by Vincent Son
 */

#ifndef __PIECE_HPP__
#define __PIECE_HPP__

#include "../includes/Drawable.hpp"
#include <memory>
#include <utility>
#include <SFML/Graphics.hpp>

enum PieceState {
    NONE,
	TO_FALL,
	FALLING, // Piece is "falling" to its place on the board
    SELECTED, // The piece is selected
    MATCHED, // The piece is in a match. Waiting for deletion,
	SWAPPING // The piece is swapping with another piece
};

class Piece : public Drawable
{
	// TODO: Load qu'une seule texture, au lieu de load la texture a chaque fois qu'on a une pi�ce.
	// Probably like the TextureManager I made in Guneodros
	public:
		Piece(int type, std::pair<int, int> position);
		const int getType() const;
		const sf::Sprite *getSprite() const;
		const sf::Vector2f getPosition() const;
		void setPosition(sf::Vector2f pos);
		const bool isSelected() const;
		void setStatus(PieceState state);
		const PieceState getStatus() const;
		void setTargetPosition(sf::Vector2f pos);
		const sf::Vector2f getTargetPosition() const;
		void update();
		~Piece() = default;
	private:
		int mType;
		std::pair<float, float> mPosition;
		PieceState mState = NONE;
		sf::Vector2f mTargetPosition = {-1, -1};
};

#endif /* __PIECE_HPP__ */