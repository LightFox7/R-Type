#pragma once

#include "Core.hpp"

class Button {
    public:
        enum ButtonStatus {
            IDLE,
            PRESSED,
            RELEASED
        };
        virtual ~Button() = default;
        virtual void draw(void) = 0;
        virtual void draw(float mdr) = 0;
        virtual void computeStatus(void) = 0;
        virtual ButtonStatus getStatus() const = 0;
        virtual void setText(std::string &str) = 0;
};
