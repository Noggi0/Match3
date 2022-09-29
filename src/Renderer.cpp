/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/Renderer.hpp"
#include "../includes/Defines.hpp"
#include <iostream>

Renderer::Renderer()
    : window(std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), "Match 3")), frametime(0.0f), newTime(0.0f), currentTime(0.0f)
{
    this->setFramerate(144);
    std::cout << "------- Renderer created -------" << std::endl;
}

void Renderer::draw(std::vector<Piece *> pieces)
{
    this->newTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    this->frametime = this->newTime - this->currentTime;

    if (this->frametime < 1.0f / this->framerate)
        return;

    this->currentTime = this->newTime;

    window->clear();
    window->setTitle("Match 3 - " + std::to_string(1000 / this->frametime) + " FPS");
    for (auto& piece : pieces) {
        window->draw(*piece->getSprite());
    }
    window->display();
}

void Renderer::setWindowSize(int width, int height)
{
    window->setSize(sf::Vector2u(width, height));
}

sf::RenderWindow* Renderer::getWindow() const
{
    return window.get();
}

void Renderer::setFramerate(int framerate)
{
    window->setFramerateLimit(framerate);
    this->framerate = std::move(framerate);
}