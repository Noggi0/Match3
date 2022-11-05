/**
 * Match 3 game, by Vincent Son
 */

#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Renderer.hpp"
#include "EventHandling.hpp"
#include "Buttons.hpp"
#include "Board.hpp"
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>

enum class GameState
{
    MAIN_MENU,
    PLAYING,
    PAUSED,
    EXIT
};

class Game
{
    public:
        Game();
        const GameState getGameState() const;
        void setGameState(GameState state);
        void startLevel();
        void loadMainMenuElements();
        void renderMainMenu();
        void update();
        ~Game() = default;
    private:
        GameState mState;
        std::unique_ptr<Renderer> mRenderer;
        std::unique_ptr<Board> mBoard;
        std::vector<Drawable*> mMainMenuElements;
};

#endif /* __GAME_HPP__ */