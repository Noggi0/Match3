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
    this->state = BoardState::NORMAL;
    std::random_device device;
    this->rng = std::mt19937(device());
    this->random = std::uniform_int_distribution<std::mt19937::result_type>(0, 7);
    this->score = 0;
    int offsetX = (WIDTH / 2) - (35 * this->width);
    int offsetY = (HEIGHT / 2) - (35 * this->height);
    this->boardPosition = { offsetX, offsetY };
}

void Board::initBoard()
{
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width; y++)
        {
            std::pair<int, int> position = std::make_pair(boardPosition.x + (70 * y), boardPosition.y + (70 * i));
            this->pieces.push_back(new Piece(this->random(this->rng), position));

            Drawable* boardBackgroundElement = new Drawable();
            if (!boardBackgroundElement->loadSprite(ASSETS_PATH + "/stone background.png"))
                throw std::runtime_error("Couldn't load stone background sprite");
            boardBackgroundElement->setScale(0.14f, 0.14f);
            boardBackgroundElement->setPosition(position.first - 10, position.second - 10);
            this->boardBackground.push_back(std::move(boardBackgroundElement));
        }
    }
}

const std::vector<Piece *> Board::getPieces() const
{
    return this->pieces;
}

const std::vector<Drawable*> Board::getBoardBackground() const
{
    return this->boardBackground;
}

const BoardState Board::getState() const
{
    return this->state;
}

void Board::setState(BoardState state)
{
    this->state = state;
}

const int Board::getSelectedPieceIndex() const
{
    return this->selectedPieceIndex;
}

void Board::setSelectedPieceIndex(int index)
{
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

    if (neighbour->getPosition().x == selected->getPosition().x + 70 && neighbour->getPosition().y == selected->getPosition().y)
        return true;
    else if (neighbour->getPosition().x == selected->getPosition().x - 70 && neighbour->getPosition().y == selected->getPosition().y)
        return true;
    else if (neighbour->getPosition().y == selected->getPosition().y + 70 && neighbour->getPosition().x == selected->getPosition().x)
        return true;
    else if (neighbour->getPosition().y == selected->getPosition().y - 70 && neighbour->getPosition().x == selected->getPosition().x)
        return true;
    return false;
}

void Board::swapPieces(int selectedPieceIndex, int index)
{
    Piece* selected = this->pieces.at(selectedPieceIndex);
    Piece* otherPiece = this->pieces.at(index);

    selected->setTargetPosition(otherPiece->getPosition());
    selected->setStatus(PieceState::SWAPPING);
    otherPiece->setTargetPosition(selected->getPosition());
    otherPiece->setStatus(PieceState::SWAPPING);

    this->lastMovedPiecesIndex = std::make_pair(selectedPieceIndex, index);

    Piece* tempPiece = selected;
    this->pieces.at(this->selectedPieceIndex) = otherPiece;
    this->pieces.at(index) = tempPiece;
}

bool Board::checkForMatches()
{
    /**
    Iterate the whole grid, starting from top left.

    At every point on the grid until and including the 6th column, check one tile right,
    and down (you do not need to check left and up because you've done this)

    If they match, then try checking one more tile along/down. If they don't, move to the next tile along.
    Handle out-of-board errors as 'not the same'.

    When you finish the 8th column, move down a row.
    **/

    // x x x x x x
    // x x x x x x
    // x x x x x x
    // x x x x x x

    bool matched = false;

    if (this->state == BoardState::WAITING)
        return false;

    for (int i = 0; i < this->pieces.size(); i++)
    {
        if (i % width < width - 2 &&  this->pieces.at(i)->getType() == this->pieces.at(i + 1)->getType())
        {
            if (this->pieces.at(i)->getType() == this->pieces.at(i + 2)->getType())
            {
                this->pieces.at(i)->setStatus(PieceState::MATCHED);
                this->pieces.at(i + 1)->setStatus(PieceState::MATCHED);
                this->pieces.at(i + 2)->setStatus(PieceState::MATCHED);
                matched = true;
            }
        }

        if ((i / width) < height - 2 && (this->pieces.at(i)->getType() == this->pieces.at(i + width)->getType()))
        {
            if (this->pieces.at(i)->getType() == this->pieces.at(i + (width * 2))->getType())
            {
                this->pieces.at(i)->setStatus(PieceState::MATCHED);
                this->pieces.at(i + width)->setStatus(PieceState::MATCHED);
                this->pieces.at(i + (width * 2))->setStatus(PieceState::MATCHED);
                matched = true;
            }
        }
    }

    for (int i = 0; i < this->pieces.size(); i++)
    {
        if (this->pieces.at(i)->getStatus() == PieceState::MATCHED)
        {
            auto position = this->pieces.at(i)->getPosition();
            this->pieces.erase(this->pieces.begin() + i);
            this->pieces.insert(this->pieces.begin() + i, new Piece(this->random(this->rng), std::make_pair(position.x, position.y)));
            this->score += 10;
        }
    }
    std::cout << "Score: " << this->score << std::endl;
    return matched;
}

const bool Board::isWaiting()
{
    for (const auto& piece : this->pieces)
    {
        if (piece->getStatus() == PieceState::SWAPPING)
            return true;
    }
    return false;
}

void Board::update()
{
    if (this->state == BoardState::WAITING && !this->isWaiting())
    {
        this->setState(BoardState::NORMAL);
        if (!this->checkForMatches())
        {
            this->swapPieces(this->lastMovedPiecesIndex.first, this->lastMovedPiecesIndex.second);
        }
    }
    else
    {
        this->checkForMatches();
    }
}