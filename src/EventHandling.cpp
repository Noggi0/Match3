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
	auto pieces = board->getPieces();

	for (int row = 0; row < pieces.size(); row++)
	{
		for (int col = 0; col < pieces[row].size(); col++)
		{
			if (pieces[row][col] == nullptr)
				continue;
			sf::Vector2f piecePosition = pieces[row][col]->getPosition();

			if (x > piecePosition.x && x < piecePosition.x + 60 && y > piecePosition.y && y < piecePosition.y + 60)
			{
				if (board->getState() != BoardState::SELECTING)
				{
					pieces[row][col]->setStatus(PieceState::SELECTED);
					board->setState(BoardState::SELECTING);
					board->setSelectedPieceCoord({row, col});
					break;
				}
				else
				{
					board->setState(BoardState::WAITING);
					if (board->isNeighbour({row, col}))
					{
						board->swapPieces(board->getSelectedPieceCoord(), {row, col});
						break;
					}
					else
					{
						board->setState(BoardState::NORMAL);
						auto [row, column] = board->getSelectedPieceCoord();
						board->getPieces().at(row).at(column)->setStatus(PieceState::NONE);
						board->setSelectedPieceCoord({row, col	});
						break;
					}
				}
			}
			index++;
		}
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