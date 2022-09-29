/**
 * Match 3 game, by Vincent Son
 */

#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "Piece.hpp"
#include <vector>
#include <random>

enum State {
    NONE,
    SELECTED, // A piece has been selected
    WAITING // Waiting for pieces to move
};

class Board
{
    public:
        Board() = default;
        Board(int width, int height, int typesNb = 3);
        void populate();
        const std::vector<Piece *> getPieces() const;
        const State getState() const;
        void setState(State state);
        const int getSelectedPieceIndex() const;
        void setSelectedPieceIndex(int index);
        bool isNeighbour(int index) const;
        void swapPieces(int index);
        void checkForMatches();
        ~Board() = default;
    private:
        int width;
        int height;
        int typesNb;
        std::vector<Piece *> pieces;
        State state;
        int selectedPieceIndex = -1;
        std::mt19937 rng;
        std::uniform_int_distribution<std::mt19937::result_type> random;
};

#endif /* __BOARD_HPP__ */