/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/Renderer.hpp"
#include "../includes/Defines.hpp"
#include <iostream>

Renderer::Renderer()
    : mWindow(std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), "Match 3")), mFrametime(0.0f), mNewTime(0.0f), mCurrentTime(0.0f)
{
    this->setFramerate(144);
    std::cout << "------- Renderer created -------" << std::endl;
}

void Renderer::drawLevel(const std::vector<std::vector<Piece *>>& pieces, const std::vector<Drawable*>& boardBackground, int score)
{
    this->initNewFrame();

    for (const auto& drawable : boardBackground)
        mWindow->draw(*drawable->getSprite());

    for (int row = 0; row < pieces.size(); row++)
    {
        for (int col = 0; col < pieces[row].size(); col++)
        {
            if (pieces[row][col] != nullptr)
            {
                pieces[row][col]->update();
                mWindow->draw(*pieces[row][col]->getSprite());
            }
        }
    }

    sf::Font font;
    if (!font.loadFromFile(ASSETS_PATH + "arial.ttf"))
    {
        throw std::runtime_error("Can't load font");
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(std::to_string(score));
    scoreText.setPosition(mWindow->getSize().x / 2 - scoreText.getGlobalBounds().width / 2, 0);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setCharacterSize(42);
    mWindow->draw(scoreText);
}

void Renderer::drawMenu(const std::vector<Drawable *> &menuElements)
{
    this->initNewFrame();

    for (const auto& drawable : menuElements)
        mWindow->draw(*drawable->getSprite());
}

void Renderer::initNewFrame()
{
    mNewTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    mFrametime = (mNewTime - mCurrentTime) / 1000.0f;

    if (mFrametime < 1.0f / mFramerate)
        return;

    mCurrentTime = mNewTime;

    mWindow->clear();
    mWindow->setTitle("Match 3 - " + std::to_string(1.0f / mFrametime) + " FPS");
}

void Renderer::display()
{
    mWindow->display();
}

void Renderer::setWindowSize(int width, int height)
{
    mWindow->setSize(sf::Vector2u(width, height));
}

sf::RenderWindow* Renderer::getWindow() const
{
    return mWindow.get();
}

void Renderer::setFramerate(int framerate)
{
    mWindow->setFramerateLimit(framerate);
    mFramerate = framerate;
}

const sf::Vector2i Renderer::getWindowCenter() const
{
#ifdef __APPLE__
    return sf::Vector2i(mWindow->getSize().x / 2, mWindow->getSize().y / 2);
#else
    return sf::Vector2i(mWindow->getSize().x, mWindow->getSize().y);
#endif
}