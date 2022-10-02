/**
 * Match 3 game, by Vincent Son
 */

#ifndef __PIECE_HPP__
#define __PIECE_HPP__

#include <memory>
#include <utility>
#include <SFML/Graphics.hpp>

enum PieceState {
    NONE,
    SELECTED, // The piece is selected
    MATCHED // The piece is in a match. Waiting for deletion
};

class Piece
{
	// TODO: Load qu'une seule texture, au lieu de load la texture a chaque fois qu'on a une pi�ce.
	// TODO: Derive de Drawable i guess ? �a rendrait le draw call g�n�rique
	public:
		Piece(int type, std::pair<int, int> position);
		const int getType() const;
		const sf::Sprite *getSprite() const;
		const sf::Vector2f getPosition() const;
		void setPosition(sf::Vector2f pos);
		const bool isSelected() const;
		void setSelected(bool selected);
		~Piece() = default;
	private:
		int type;
		std::pair<int, int> position;
		std::unique_ptr<sf::Sprite> sprite;
		std::unique_ptr<sf::Texture> texture;
		PieceState state = NONE;
};

#endif /* __PIECE_HPP__ */