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
        void drawLevel(std::vector<Piece *> pieces, std::vector<Drawable*> boardBackground);
        void display();
        sf::RenderWindow* getWindow() const;
        void setWindowSize(int width, int height);
        void setFramerate(int framerate);
        ~Renderer() = default;
    private:
        std::unique_ptr<sf::RenderWindow> mWindow;
        double mFrametime;
        double mNewTime;
        double mCurrentTime;
        int mFramerate;
};

#endif /* __RENDERER_HPP__ */