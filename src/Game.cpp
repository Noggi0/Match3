/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/Game.hpp"

Game::Game()
    : mState(GameState::MAIN_MENU)
{
    mRenderer = std::make_unique<Renderer>();
    mBoard = std::make_unique<Board>(8, 4);
    loadMainMenuElements();
}

GameState Game::getGameState() const
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
        sf::Event event {};
        
        while (mRenderer->getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mRenderer->getWindow()->close();
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (mState == GameState::PLAYING)
                    handleMouseClicksForLevel(&event, mBoard.get());
                else if (mState == GameState::MAIN_MENU)
                    handleMouseClicksForMainMenu(&event, mMainMenuElements);
            }
            else if (event.type == sf::Event::Resized)
                mRenderer->getWindow()->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::M)
                    mState = GameState::MAIN_MENU;
                else if (event.key.code == sf::Keyboard::P)
                    mState = GameState::PLAYING;
                else if (event.key.code == sf::Keyboard::R)
                    mBoard->shuffleBoard();
                else if (event.key.code == sf::Keyboard::Escape)
                    mRenderer->getWindow()->close();
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (mState == GameState::MAIN_MENU)
                {
                    for (const auto &element : mMainMenuElements)
                    {
                        if (element == mMainMenuElements.front()) // ignore background which is always first
                            continue;
                        if (element->getSprite()->getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                            element->setScale(1.01f, 1.01f);
                        else
                            element->setScale(1.0f, 1.0f);
                    }
                }
            }
        }
        switch (mState)
        {
            case GameState::MAIN_MENU:
                renderMainMenu();
                break;
            case GameState::PLAYING:
                mBoard->update();
                mRenderer->drawLevel(mBoard->getPieces(), mBoard->getBoardBackground(), mBoard->getScore());
                mRenderer->display();
                break;
            case GameState::PAUSED:
                break;
            case GameState::SETTINGS:
                loadSettingsMenuElements();
                renderSettingsMenu();
                break;
            case GameState::EXIT:
                mRenderer->getWindow()->close();
                break;
        }
    }
}

void Game::renderMainMenu()
{
    mRenderer->drawMenu(mMainMenuElements);
    mRenderer->display();
}

void Game::loadMainMenuElements()
{
    int x, y;
    auto *background = new Drawable();
    background->loadSprite(ASSETS_PATH + "/background.png");
    background->setPosition(0, 10);
    mMainMenuElements.push_back(background);

    auto *playButton = new Button();
    playButton->loadSprite(ASSETS_PATH + "/Play Button.png");
    x = (mRenderer->getWindow()->getSize().x / 2.0f) - (playButton->getSprite()->getGlobalBounds().width / 2);
    y = 0;
    playButton->setPosition(x, y);
    playButton->setCallback([this](){ mState = GameState::PLAYING; });
    mMainMenuElements.push_back(playButton);

    auto *settingsButton = new Button();
    settingsButton->loadSprite(ASSETS_PATH + "/Settings Button.png");
    x = (mRenderer->getWindow()->getSize().x / 2) - (settingsButton->getSprite()->getGlobalBounds().width / 2);
    y = playButton->getSprite()->getGlobalBounds().height + 10;
    settingsButton->setPosition(x, y);
    settingsButton->setCallback([this](){ mState = GameState::PAUSED; std::cout << "PAUSED" << std::endl; });
    mMainMenuElements.push_back(settingsButton);

    auto *quitButton = new Button();
    quitButton->loadSprite(ASSETS_PATH + "/Quit Button.png");
    x = (mRenderer->getWindow()->getSize().x / 2) - (quitButton->getSprite()->getGlobalBounds().width / 2);
    y = settingsButton->getSprite()->getGlobalBounds().height + settingsButton->getSprite()->getGlobalBounds().top + 10;
    quitButton->setPosition(x, y);
    quitButton->setCallback([this](){ this->mRenderer->getWindow()->close(); });
    mMainMenuElements.push_back(quitButton);
}

void Game::loadSettingsMenuElements()
{
    // Maybe create settings file beforehand ?
    // Because we need to read this config file and populate fields accordingly
}

void Game::renderSettingsMenu()
{

}