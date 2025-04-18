/**
 * Match 3 game, by Vincent Son
 */

#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "Defines.hpp"
#include "Piece.hpp"
#include <vector>
#include <random>

struct Coord {
    int row;
    int column;
};

enum BoardState {
    NORMAL,
    SELECTING, // A piece has been selected
    WAITING // Waiting for pieces to move
};

class Board
{
    public:
        Board() = default;
        Board(int width, int height, int typesNb = 3);
        void initBoard();
        const std::vector<std::vector<Piece*>> getPieces() const;
        const std::vector<Drawable*> getBoardBackground() const;
        const BoardState getState() const;
        void setState(BoardState state);
        const Coord getSelectedPieceCoord() const;
        void setSelectedPieceCoord(Coord index);
        bool isNeighbour(Coord coords) const;
        void swapPieces(Coord selectedPieceCoords, Coord otherPieceCoords, bool keepLastMoved = false);
        bool checkForMatches();
        const bool isWaiting();
        void shuffleBoard();
        void makePiecesFall();
        void fillHoles();
        void update();
        void handleResize(int newWidth, int newHeight);
        int getScore() const;
        ~Board() = default;
    private:
        int mWidth;
        int mHeight;
        int mTypesNb;
        sf::Vector2i mBoardPosition;
        std::vector<std::vector<Piece*>> mPieces;
        std::vector<Drawable*> mBoardBackground;
        BoardState mState;
        Coord mSelectedPieceCoord = {-1, -1};
        std::mt19937 mRng;
        std::uniform_int_distribution<std::mt19937::result_type> mRandom;
        unsigned int mScore;
        std::pair<Coord, Coord> mLastMovedPiecesCoords;
};

#endif /* __BOARD_HPP__ */