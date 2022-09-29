/**
 * Match 3 game, by Vincent Son
 */

#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__


#include "Piece.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include <vector>

class Renderer
{
    public:
        Renderer();
        void draw(std::vector<Piece *> pieces);
        sf::RenderWindow* getWindow() const;
        void setWindowSize(int width, int height);
        void setFramerate(int framerate);
        ~Renderer() = default;
    private:
        std::unique_ptr<sf::RenderWindow> window;
        double frametime;
        double newTime;
        double currentTime;
        int framerate;
};

#endif /* __RENDERER_HPP__ */