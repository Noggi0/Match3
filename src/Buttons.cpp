/**
 * Match 3 game, by Vincent Son
 */

#include "../includes/Buttons.hpp"

void Button::setCallback(std::function<void()> callback)
{
    mCallback = std::move(callback);
}

void Button::clicked()
{
    mCallback();
}