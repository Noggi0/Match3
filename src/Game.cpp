/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/Game.hpp"

Game::Game()
    : mState(GameState::MAIN_MENU)
{
    mRenderer = std::make_unique<Renderer>();
    mBoard = std::make_unique<Board>(8, 4);
}

const GameState Game::getGameState() const
{
    return mState;
}

void Game::setGameState(GameState state)
{
    mState = state;
}

void Game::startLevel()
{
    mBoard->initBoard();
    mState = GameState::PLAYING;
}

void Game::update()
{
    while (mRenderer->getWindow()->isOpen())
    {
        sf::Event event;
        
        while (mRenderer->getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mRenderer->getWindow()->close();
            else if (event.type == sf::Event::MouseButtonReleased)
                handleMouseClicks(&event, mBoard.get());
            else if (event.type == sf::Event::Resized)
                mRenderer->getWindow()->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        }
        switch (mState)
        {
            case GameState::MAIN_MENU:
                // renderMainMenu();
                break;
            case GameState::PLAYING:
                mBoard->update();
                mRenderer->drawLevel(mBoard->getPieces(), mBoard->getBoardBackground());
                mRenderer->display();
                break;
            case GameState::PAUSED:
                break;
            case GameState::EXIT:
                mRenderer->getWindow()->close();
                break;
        }
    }
}