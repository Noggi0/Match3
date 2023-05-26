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
    SETTINGS,
    EXIT
};

class Game
{
    public:
        Game();
        GameState getGameState() const;
        void setGameState(GameState state);
        void startLevel();
        void loadMainMenuElements();
        void renderMainMenu();
        void loadSettingsMenuElements();
        void renderSettingsMenu();
        void update();
        ~Game() = default;
    private:
        GameState mState;
        std::unique_ptr<Renderer> mRenderer;
        std::unique_ptr<Board> mBoard;
        std::vector<Drawable*> mMainMenuElements;
        std::vector<Drawable*> mSettingsMenuElements;
};

#endif /* __GAME_HPP__ */