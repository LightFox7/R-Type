#pragma once

#include "Button.hpp"

class RectButton : public Button {
    public:
        RectButton(Core &core, mystructs::vector2d<float> const &size, mystructs::vector2d<float> const &pos, std::string const &text, sf::Color const &color, sf::Color const &textcolor);
        ~RectButton();
        void placeText(void);
        void draw(void);
        void draw(float mdr);
        void computeStatus(void);
        ButtonStatus getStatus(void) const;
        void setText(std::string &str);

    private:
        Core &_core;
        ButtonStatus _status;
        mystructs::vector2d<float> _pos;
        mystructs::vector2d<float> _size;
        std::string _text;
        sf::Color _rectColor;
        sf::Color _textColor;
};
