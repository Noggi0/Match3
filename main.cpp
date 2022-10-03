/**
 * Match 3 game, by Vincent Son
 */

#include "includes/Renderer.hpp"
#include "includes/Board.hpp"
#include "includes/Defines.hpp"
#include "includes/EventHandling.hpp"

int main()
{
    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
    std::unique_ptr<Board> board = std::make_unique<Board>(8, 4);
    board->populate();

    while (renderer->getWindow()->isOpen()) {
        sf::Event event;

        while (renderer->getWindow()->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                renderer->getWindow()->close();
            else if (event.type == sf::Event::MouseButtonReleased)
                handleMouseClicks(&event, board.get());
            else if (event.type == sf::Event::Resized)
                renderer->getWindow()->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        }
        board->update();
        renderer->draw(board->getPieces());
    }
    return 0;
}