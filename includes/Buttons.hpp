/**
 * Match 3 game, by Vincent Son
 */

#ifndef __BUTTONS_HPP__
#define __BUTTONS_HPP__

#include "Drawable.hpp"
#include <memory>
#include <functional>

class Button : public Drawable
{
    public:
        Button() = default;
        void setCallback(std::function<void()> callback);
        void clicked();
        ~Button() = default;
    private:
        std::function<void()> mCallback;
};

#endif /* __BUTTONS_HPP__ */
