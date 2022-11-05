/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/EventHandling.hpp"
#include "../includes/Buttons.hpp"
#include <iostream>

void handleMouseClicksForLevel(sf::Event* event, Board* board)
{
	int x = event->mouseButton.x;
	int y = event->mouseButton.y;

	int index = 0;
	for (const auto &piece : board->getPieces())
	{
		sf::Vector2f piecePosition = piece->getPosition();

		if (x > piecePosition.x && x < piecePosition.x + 60 && y > piecePosition.y && y < piecePosition.y + 60)
		{
			if (board->getState() != BoardState::SELECTING)
			{
				piece->setStatus(PieceState::SELECTED);
				board->setState(BoardState::SELECTING);
				board->setSelectedPieceIndex(index);
			}
			else
			{
				board->setState(BoardState::WAITING);
				if (board->isNeighbour(index))
				{
					board->swapPieces(board->getSelectedPieceIndex(), index);
				}
				else
				{
					board->setState(BoardState::NORMAL);
					board->getPieces().at(board->getSelectedPieceIndex())->setStatus(PieceState::NONE);
					board->setSelectedPieceIndex(-1);
				}
			}
		}
		index++;
	}
}

void handleMouseClicksForMainMenu(sf::Event* event, const std::vector<Drawable*> &menuElements)
{
    int x = event->mouseButton.x;
    int y = event->mouseButton.y;

    int index = 0;
    for (const auto &element : menuElements)
    {
        if (index == 0)
        {
            index++;
            continue;
        }

        auto* button = dynamic_cast<Button*>(element);

        auto globalBounds = element->getSprite()->getGlobalBounds();

        if (globalBounds.contains(x, y))
        {
            button->clicked();
        }
        index++;
    }
}