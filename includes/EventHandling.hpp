/**
 * Match 3 game, by Vincent Son
 */

#ifndef __EVENT_HANDLING__
#define __EVENT_HANDLING__

#include "Board.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

void handleMouseClicks(sf::Event* event, Board* board);

#endif /* __EVENT_HANDLING__ */