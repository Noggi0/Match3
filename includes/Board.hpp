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
        int width;
        int height;
        int typesNb;
        sf::Vector2i boardPosition;
        std::vector<Piece*> pieces;
        std::vector<Drawable*> boardBackground;
        BoardState state;
        int selectedPieceIndex = -1;
        std::mt19937 rng;
        std::uniform_int_distribution<std::mt19937::result_type> random;
        unsigned int score;
        std::pair<int, int> lastMovedPiecesIndex;
};

#endif /* __BOARD_HPP__ */