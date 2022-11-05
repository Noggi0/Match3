/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/Board.hpp"
#include <utility>
#include <iostream>

Board::Board(int width, int height, int typesNb)
    : mWidth(width), mHeight(height), mTypesNb(typesNb)
{
    std::cout << "------- Board created -------" << std::endl;
    this->mState = BoardState::NORMAL;
    std::random_device device;
    this->mRng = std::mt19937(device());
    this->mRandom = std::uniform_int_distribution<std::mt19937::result_type>(0, 7);
    this->mScore = 0;
    int offsetX = (WIDTH / 2) - (35 * this->mWidth);
    int offsetY = (HEIGHT / 2) - (35 * this->mHeight);
    this->mBoardPosition = { offsetX, offsetY };
}

void Board::initBoard()
{
    for (int i = 0; i < mHeight; i++)
    {
        for (int y = 0; y < mWidth; y++)
        {
            std::pair<int, int> position = std::make_pair(mBoardPosition.x + (70 * y), mBoardPosition.y + (70 * i));
            mPieces.push_back(new Piece(mRandom(this->mRng), position));

            Drawable* boardBackgroundElement = new Drawable();
            if (!boardBackgroundElement->loadSprite(ASSETS_PATH + "/stone background.png"))
                throw std::runtime_error("Couldn't load stone background sprite");
            boardBackgroundElement->setScale(0.14f, 0.14f);
            boardBackgroundElement->setPosition(position.first - 10, position.second - 10);
            mBoardBackground.push_back(std::move(boardBackgroundElement));
        }
    }
}

const std::vector<Piece *> Board::getPieces() const
{
    return mPieces;
}

const std::vector<Drawable*> Board::getBoardBackground() const
{
    return mBoardBackground;
}

const BoardState Board::getState() const
{
    return mState;
}

void Board::setState(BoardState state)
{
    mState = state;
}

const int Board::getSelectedPieceIndex() const
{
    return mSelectedPieceIndex;
}

void Board::setSelectedPieceIndex(int index)
{
    mSelectedPieceIndex = index;
}

bool Board::isNeighbour(int index) const
{
    Piece* neighbour = mPieces.at(index);
    Piece* selected = mPieces.at(mSelectedPieceIndex);

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
    Piece* selected = mPieces.at(selectedPieceIndex);
    Piece* otherPiece = mPieces.at(index);

    selected->setTargetPosition(otherPiece->getPosition());
    selected->setStatus(PieceState::SWAPPING);
    otherPiece->setTargetPosition(selected->getPosition());
    otherPiece->setStatus(PieceState::SWAPPING);

    mLastMovedPiecesIndex = std::make_pair(selectedPieceIndex, index);

    Piece* tempPiece = selected;
    mPieces.at(mSelectedPieceIndex) = otherPiece;
    mPieces.at(index) = tempPiece;
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

    // TODO: Allow different matching patterns.

    bool matched = false;

    if (mState == BoardState::WAITING)
        return false;

    for (int i = 0; i < mPieces.size(); i++)
    {
        if (i % mWidth < mWidth - 2 &&  mPieces.at(i)->getType() == mPieces.at(i + 1)->getType())
        {
            if (mPieces.at(i)->getType() == mPieces.at(i + 2)->getType())
            {
                mPieces.at(i)->setStatus(PieceState::MATCHED);
                mPieces.at(i + 1)->setStatus(PieceState::MATCHED);
                mPieces.at(i + 2)->setStatus(PieceState::MATCHED);
                matched = true;
            }
        }

        if ((i / mWidth) < mHeight - 2 && (mPieces.at(i)->getType() == mPieces.at(i + mWidth)->getType()))
        {
            if (mPieces.at(i)->getType() == mPieces.at(i + (mWidth * 2))->getType())
            {
                mPieces.at(i)->setStatus(PieceState::MATCHED);
                mPieces.at(i + mWidth)->setStatus(PieceState::MATCHED);
                mPieces.at(i + (mWidth * 2))->setStatus(PieceState::MATCHED);
                matched = true;
            }
        }
    }

    for (int i = 0; i < mPieces.size(); i++)
    {
        if (mPieces.at(i)->getStatus() == PieceState::MATCHED)
        {
            auto position = mPieces.at(i)->getPosition();
            mPieces.erase(mPieces.begin() + i);
            mPieces.insert(mPieces.begin() + i, new Piece(mRandom(mRng), std::make_pair(position.x, position.y)));
            mScore += 10;
        }
    }
    std::cout << "Score: " << mScore << std::endl;
    return matched;
}

const bool Board::isWaiting()
{
    for (const auto& piece : mPieces)
    {
        if (piece->getStatus() == PieceState::SWAPPING)
            return true;
    }
    return false;
}

void Board::update()
{
    if (mState == BoardState::WAITING && !this->isWaiting())
    {
        this->setState(BoardState::NORMAL);
        if (!this->checkForMatches())
        {
            this->swapPieces(mLastMovedPiecesIndex.first, mLastMovedPiecesIndex.second);
        }
    }
    else
    {
        this->checkForMatches();
    }
}

void Board::shuffleBoard()
{
    std::shuffle(mPieces.begin(), mPieces.end(), mRng);

    // Update positions of pieces after shuffling.
    for (int i = 0; i < mHeight; i++) {
        for (int j = 0; j < mWidth; j++) {
            sf::Vector2f position = {static_cast<float>(mBoardPosition.x + (70 * j)), static_cast<float>(mBoardPosition.y + (70 * i))};
            mPieces.at(i * mWidth + j)->setPosition(position);
        }
    }
}