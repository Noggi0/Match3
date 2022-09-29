/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/Board.hpp"
#include <utility>
#include <iostream>

Board::Board(int width, int height, int typesNb)
    : width(std::move(width)), height(std::move(height)), typesNb(std::move(typesNb))
{
    std::cout << "------- Board created -------" << std::endl;
    this->state = State::NONE;
    std::random_device device;
    this->rng = std::mt19937(device());
    this->random = std::uniform_int_distribution<std::mt19937::result_type>(0, 7);
}

void Board::populate()
{
    for (int i = 0; i < height; i++) {
        for (int y = 0; y < width; y++) {
            this->pieces.push_back(new Piece(this->random(this->rng), std::make_pair(y, i)));
        }
    }
}

const std::vector<Piece *> Board::getPieces() const
{
    return this->pieces;
}

const State Board::getState() const
{
    return this->state;
}

void Board::setState(State state)
{
    this->state = state;
}

const int Board::getSelectedPieceIndex() const
{
    return this->selectedPieceIndex;
}

void Board::setSelectedPieceIndex(int index)
{
    if (index == -1)
        this->pieces.at(this->selectedPieceIndex)->setSelected(false);
    this->selectedPieceIndex = index;
}

bool Board::isNeighbour(int index) const
{
    Piece* neighbour = this->pieces.at(index);
    Piece* selected = this->pieces.at(this->selectedPieceIndex);

    // Neighbours are the pieces around x like:
    //       y+1
    //   x-1  x  x+1
    //       y-1

    if (neighbour->getPosition().x == selected->getPosition().x + 60 && neighbour->getPosition().y == selected->getPosition().y)
        return true;
    else if (neighbour->getPosition().x == selected->getPosition().x - 60 && neighbour->getPosition().y == selected->getPosition().y)
        return true;
    else if (neighbour->getPosition().y == selected->getPosition().y + 60 && neighbour->getPosition().x == selected->getPosition().x)
        return true;
    else if (neighbour->getPosition().y == selected->getPosition().y - 60 && neighbour->getPosition().x == selected->getPosition().x)
        return true;
    return false;
}

void Board::swapPieces(int index)
{
    // TODO: add animation on swap (piece state::SWAPPING ?)

    Piece* selected = this->pieces.at(this->selectedPieceIndex);
    Piece* otherPiece = this->pieces.at(index);

    sf::Vector2f temp = selected->getPosition();
    selected->setPosition(otherPiece->getPosition());
    otherPiece->setPosition(temp);

    Piece* tempPiece = selected;
    this->pieces.at(this->selectedPieceIndex) = otherPiece;
    this->pieces.at(index) = tempPiece;

    selected->setSelected(false);
}

void Board::checkForMatches()
{
    /**
    Iterate the whole grid, starting from top left.

    At every point on the grid until and including the 6th column, check one tile right,
    and down (you do not need to check left and up because you've done this)

    If they match, then try checking one more tile along/down. If they don't, move to the next tile along.
    Handle out-of-board errors as 'not the same'.

    When you finish the 8th column, move down a row.

    This would allow much simpler code in the for loop,
    since you do not have an if structure with some code on one side, and slightly tweaked code below it.
    **/

    // x x x x x x
    // x x x x x x
    // x x x x x x
    // x x x x x x

    for (int i = 0; i < this->pieces.size(); i++) {
        if (i % width <= width - 2 &&  this->pieces.at(i)->getType() == this->pieces.at(i + 1)->getType()) {
            if (this->pieces.at(i)->getType() == this->pieces.at(i + 2)->getType()) {
                // set status to MATCHED and remove it
                std::cout << "Horizontal 3match" << std::endl;
            }
        }

        if ((i / width) < height - 2 && (this->pieces.at(i)->getType() == this->pieces.at(i + width)->getType())) {
            if (this->pieces.at(i)->getType() == this->pieces.at(i + (width * 2))->getType()) {
                // set status to MATCHED and remove it
                std::cout << "Vertical match" << std::endl;
            }
        }
    }
}