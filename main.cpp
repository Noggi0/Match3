/**
 * Match 3 game, by Vincent Son
 */

#include "includes/Game.hpp"

int main()
{
    Game game;

    game.setGameState(GameState::MAIN_MENU);
    game.update();
    return 0;
}