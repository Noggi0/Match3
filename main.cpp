/**
 * Match 3 game, by Vincent Son
 */

#include "includes/Game.hpp"

int main()
{
    Game game;

    game.setGameState(GameState::PLAYING);
    game.startLevel();
    game.update();
    return 0;
}