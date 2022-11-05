/**
 * Match 3 game, by Vincent Son
 */

#ifndef __EVENT_HANDLING__
#define __EVENT_HANDLING__

#include "Board.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

void handleMouseClicksForLevel(sf::Event* event, Board* board);

void handleMouseClicksForMainMenu(sf::Event* event, const std::vector<Drawable*> &menuElements);

#endif /* __EVENT_HANDLING__ */