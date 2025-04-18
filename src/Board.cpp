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
    this->mRandom = std::uniform_int_distribution<std::mt19937::result_type>(0, typesNb);
    this->mScore = 0;
    int offsetX = (WIDTH / 2) - (35 * this->mWidth);
    int offsetY = (HEIGHT / 2) - (35 * this->mHeight);
    this->mBoardPosition = { offsetX, offsetY };
    initBoard();
}

void Board::initBoard()
{
    mPieces = std::vector<std::vector<Piece*>>(mHeight, std::vector<Piece*>());
    for (int i = 0; i < mHeight; i++)
    {
        for (int y = 0; y < mWidth; y++)
        {
            std::pair<int, int> position = std::make_pair(mBoardPosition.x + (70 * y), mBoardPosition.y + (70 * i));
            mPieces.at(i).emplace_back(new Piece(mRandom(this->mRng), position));

            Drawable* boardBackgroundElement = new Drawable();
            if (!boardBackgroundElement->loadSprite(ASSETS_PATH + "/stone background.png"))
                throw std::runtime_error("Couldn't load stone background sprite");
            boardBackgroundElement->setScale(0.14f, 0.14f);
            boardBackgroundElement->setPosition(position.first - 10, position.second - 10);
            mBoardBackground.push_back(boardBackgroundElement);

            if (y == 0 || y == mWidth - 1)
            {
                Drawable* boardBorderElement = new Drawable();
                if (!boardBorderElement->loadSprite(ASSETS_PATH + "/frame.png"))
                    throw std::runtime_error("Couldn't load frame stone");
                boardBorderElement->setScale(0.14f, 0.14f);
                if (y == 0)
                    boardBorderElement->setPosition(position.first - 10, position.second - 10);
                else
                    boardBorderElement->setPosition(position.first + 60, position.second - 10);
                mBoardBackground.push_back(boardBorderElement);
            }
            if (i == 0 || i == mHeight - 1)
            {
                Drawable* boardBorderElement = new Drawable();
                if (!boardBorderElement->loadSprite(ASSETS_PATH + "/frame.png"))
                    throw std::runtime_error("Couldn't load frame stone");
                boardBorderElement->setScale(0.14f, 0.14f);
                if (i == 0)
                    boardBorderElement->setPosition(position.first - 10, position.second - 10);
                else
                    boardBorderElement->setPosition(position.first - 10, position.second + 60);
                boardBorderElement->setRotation(-90);
                mBoardBackground.push_back(boardBorderElement);
            }
        }
    }
}

const std::vector<std::vector<Piece*>> Board::getPieces() const
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

const Coord Board::getSelectedPieceCoord() const
{
    return mSelectedPieceCoord;
}

void Board::setSelectedPieceCoord(Coord index)
{
    mSelectedPieceCoord = index;
}

bool Board::isNeighbour(Coord coords) const
{
    const Piece* neighbour = mPieces.at(coords.row).at(coords.column);
    Piece* selected = mPieces.at(mSelectedPieceCoord.row).at(mSelectedPieceCoord.column);

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

void Board::swapPieces(Coord selectedPieceCoords, Coord otherPieceCoords, bool keepLastMoved)
{
    Piece* selected = mPieces.at(selectedPieceCoords.row).at(selectedPieceCoords.column);
    Piece* otherPiece = mPieces.at(otherPieceCoords.row).at(otherPieceCoords.column);

    if (selected == nullptr || otherPiece == nullptr)
        return;

    selected->setTargetPosition(otherPiece->getPosition());
    selected->setStatus(PieceState::SWAPPING);
    otherPiece->setTargetPosition(selected->getPosition());
    otherPiece->setStatus(PieceState::SWAPPING);

    mLastMovedPiecesCoords = std::make_pair(selectedPieceCoords, otherPieceCoords);

    Piece* tempPiece = selected;
    mPieces.at(mSelectedPieceCoord.row).at(mSelectedPieceCoord.column) = otherPiece;
    mPieces.at(otherPieceCoords.row).at(otherPieceCoords.column) = tempPiece;
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

    if (mState == BoardState::WAITING)
        return false;

    for (int row = 0; row < mPieces.size(); row++)
    {
        for (int col = 0; col < mPieces[row].size(); col++)
        {
            if (mPieces[row][col] == nullptr || mPieces[row][col + 1] == nullptr)
                continue;
            if (col < mPieces[row].size() - 2 && mPieces[row][col]->getType() == mPieces[row][col + 1]->getType())
            {
                if (mPieces[row][col + 2] == nullptr)
                    continue;
                if (mPieces[row][col]->getType() == mPieces[row][col + 2]->getType())
                {
                    mPieces[row][col]->setStatus(PieceState::MATCHED);
                    mPieces[row][col + 1]->setStatus(PieceState::MATCHED);
                    mPieces[row][col + 2]->setStatus(PieceState::MATCHED);
                    matched = true;
                }
            }

            if (row >= mPieces.size() - 2)
                continue;
            if (mPieces[row + 1][col] == nullptr)
                continue;
            if (mPieces[row][col]->getType() == mPieces[row + 1][col]->getType())
            {
                if (mPieces[row + 2][col] == nullptr)
                    continue;
                if (mPieces[row][col]->getType() == mPieces[row + 2][col]->getType())
                {
                    mPieces[row][col]->setStatus(PieceState::MATCHED);
                    mPieces[row + 1][col]->setStatus(PieceState::MATCHED);
                    mPieces[row + 2][col]->setStatus(PieceState::MATCHED);
                }
            }
        }
    }

    for (int row = 0; row < mPieces.size(); row++)
    {
        for (int col = 0; col < mPieces[row].size(); col++)
        {
            if (mPieces[row][col] == nullptr)
                continue;
            if (mPieces[row][col]->getStatus() == PieceState::MATCHED)
            {
                mPieces[row][col] = nullptr;
                mScore += 10;
            }
        }
    }

    return matched;
}

const bool Board::isWaiting()
{
    for (int row = 0; row < mPieces.size(); row++)
    {
        for (int col = 0; col < mPieces[row].size(); col++)
        {
            if (mPieces[row][col] == nullptr)
                continue;
            if (mPieces[row][col]->getStatus() == PieceState::SWAPPING || mPieces[row][col]->getStatus() == PieceState::FALLING)
                return true;
        }
    }
    return false;
}

void Board::makePiecesFall()
{
    for (int row = mPieces.size() - 1; row >= 0; row--) {
        for (int col = 0; col < mPieces[row].size(); col++) {
            if (row >= 1)
            {
                if (mPieces[row][col] == nullptr && mPieces[row - 1][col] != nullptr)
                {
                    const sf::Vector2f newCoords = {mPieces[row - 1][col]->getPosition().x, static_cast<float>( mBoardPosition.y + ((row) * 70))};
                    mPieces[row - 1][col]->setTargetPosition(newCoords);
                    mPieces[row - 1][col]->setStatus(PieceState::FALLING);

                    std::swap(mPieces[row][col], mPieces[row - 1][col]);
                }
            }
            else
            {
                if (mPieces[row][col] == nullptr)
                {
                    std::pair<int, int> position = std::make_pair(mBoardPosition.x + (70 * col), mBoardPosition.y);
                    mPieces[row][col] = new Piece(mRandom(this->mRng), position);
                }
            }
        }
    }
}


void Board::update()
{
    if (mState == BoardState::WAITING && !this->isWaiting())
    {
        this->setState(BoardState::NORMAL);
        if (!this->checkForMatches())
        {
            this->swapPieces(mLastMovedPiecesCoords.first, mLastMovedPiecesCoords.second);
        }
    }
    else
    {
        this->checkForMatches();
        this->makePiecesFall();
    }
}

void Board::handleResize(int newWidth, int newHeight)
{
    int offsetX = (newWidth / 2) - (35 * this->mWidth);
    int offsetY = (newHeight / 2) - (35 * this->mHeight);
    this->mBoardPosition = { offsetX, offsetY };
    std::cout << "Handle Resize" << std::endl;
    int count = 0;
    for (int i = 0; i < mHeight; i++)
    {
        for (int j = 0; j < mWidth; j++)
        {
            sf::Vector2f position = { static_cast<float>(mBoardPosition.x + (70 * j)), static_cast<float>(mBoardPosition.y + (70 * i)) };
            mPieces.at(i).at(j)->setPosition(position);

            mBoardBackground.at(count)->setPosition(position.x - 10, position.y - 10);
            count++;

            if (j == 0 || j == mWidth - 1)
            {
                
                if (j == 0)
                    mBoardBackground.at(count)->setPosition(position.x - 10, position.y - 10);
                else
                    mBoardBackground.at(count)->setPosition(position.x + 60, position.y - 10);
                count++;
            }
            if (i == 0 || i == mHeight - 1)
            {
                if (i == 0)
                    mBoardBackground.at(count)->setPosition(position.x - 10, position.y - 10);
                else
                    mBoardBackground.at(count)->setPosition(position.x - 10, position.y + 60);
                count++;
            }
        }
    }
}

void Board::shuffleBoard()
{
    std::shuffle(mPieces.begin(), mPieces.end(), mRng);

    // Update internal positions of pieces after shuffling.
    for (int i = 0; i < mHeight; i++) {
        for (int j = 0; j < mWidth; j++) {
            sf::Vector2f position = { static_cast<float>(mBoardPosition.x + (70 * j)), static_cast<float>(mBoardPosition.y + (70 * i)) };
            mPieces.at(i).at(j)->setPosition(position);
        }
    }
}

int Board::getScore() const
{
    return mScore;
}