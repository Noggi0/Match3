/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/EventHandling.hpp"
#include <iostream>

void handleMouseClicks(sf::Event* event, Board* board)
{
	int x = event->mouseButton.x;
	int y = event->mouseButton.y;

	int index = 0;
	for (auto &piece : board->getPieces()) {
		sf::Vector2f piecePosition = piece->getPosition();

		if (x > piecePosition.x && x < piecePosition.x + 60 && y > piecePosition.y && y < piecePosition.y + 60) {
			if (board->getState() != BoardState::SELECTING) {
				std::cout << "------- Piece clicked -------" << std::endl;
				piece->setStatus(PieceState::SELECTED);
				board->setState(BoardState::SELECTING);
				board->setSelectedPieceIndex(index);
			}
			else {
				board->setState(BoardState::WAITING);
				if (board->isNeighbour(index))
					board->swapPieces(index); // TODO: if removed == 0, swap back to previous state
				else {
					board->setState(BoardState::NORMAL);
					board->getPieces().at(board->getSelectedPieceIndex())->setStatus(PieceState::NONE);
					board->setSelectedPieceIndex(-1);
				}
			}
		}
		index++;
	}
}