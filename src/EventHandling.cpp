/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/EventHandling.hpp"
#include <iostream>

void handleMouseClicks(sf::Event* event, Board* board)
{
	std::cout << "------- Clicked x: " << event->mouseButton.x << ", y: " << event->mouseButton.y << " -------" << std::endl;
	int x = event->mouseButton.x;
	int y = event->mouseButton.y;

	int index = 0;
	for ( auto piece : board->getPieces()) {
		sf::Vector2f piecePosition = piece->getPosition();

		if (x > piecePosition.x && x < piecePosition.x + 60 && y > piecePosition.y && y < piecePosition.y + 60) {
			if (board->getState() != State::SELECTED) {
				std::cout << "------- Piece clicked -------" << std::endl;
				piece->setSelected(true);
				board->setState(State::SELECTED);
				board->setSelectedPieceIndex(index);
			}
			else {
				board->setState(State::NONE);
				if (board->isNeighbour(index))
					board->swapPieces(index);
				board->setSelectedPieceIndex(-1);
			}
		}
		index++;
	}
}