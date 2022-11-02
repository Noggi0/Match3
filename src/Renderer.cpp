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

void Renderer::draw(std::vector<Piece *> pieces, std::vector<Drawable*> boardBackground)
{
    mNewTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    mFrametime = mNewTime - mCurrentTime;

    if (mFrametime < 1.0f / mFramerate)
        return;

    mCurrentTime = mNewTime;

    mWindow->clear();
    mWindow->setTitle("Match 3 - " + std::to_string(1000 / mFrametime) + " FPS");
    for (const auto& drawable : boardBackground)
        mWindow->draw(*drawable->getSprite());
    for (const auto& piece : pieces)
    {
        piece->update();
        mWindow->draw(*piece->getSprite());
    }
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
    mFramerate = std::move(framerate);
}