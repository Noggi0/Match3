/**
 * Match 3 game, by Vincent Son
 */

#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "Defines.hpp"
#include "Piece.hpp"
#include <vector>
#include <random>

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
        const std::vector<Piece *> getPieces() const;
        const std::vector<Drawable*> getBoardBackground() const;
        const BoardState getState() const;
        void setState(BoardState state);
        const int getSelectedPieceIndex() const;
        void setSelectedPieceIndex(int index);
        bool isNeighbour(int index) const;
        void swapPieces(int selectedPieceIndex, int index);
        bool checkForMatches();
        const bool isWaiting();
        void update();
        ~Board() = default;
    private:
        int mWidth;
        int mHeight;
        int mTypesNb;
        sf::Vector2i mBoardPosition;
        std::vector<Piece*> mPieces;
        std::vector<Drawable*> mBoardBackground;
        BoardState mState;
        int mSelectedPieceIndex = -1;
        std::mt19937 mRng;
        std::uniform_int_distribution<std::mt19937::result_type> mRandom;
        unsigned int mScore;
        std::pair<int, int> mLastMovedPiecesIndex;
};

#endif /* __BOARD_HPP__ */