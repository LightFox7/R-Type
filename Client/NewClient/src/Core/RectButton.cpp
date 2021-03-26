#include "RectButton.hpp"

RectButton::RectButton(Core &core, mystructs::vector2d<float> const &size, mystructs::vector2d<float> const &pos, std::string const &text, sf::Color const &color, sf::Color const &textcolor) : _core(core), _status(IDLE), _pos(pos), _size(size), _text(text)
{
    _textColor = textcolor;
    _rectColor = color;
}

RectButton::~RectButton()
{
}

void RectButton::draw()
{
    int charsize = ((float)_size.y / 1.5);
    int textposx = (float)(_pos.x) + (float)(((float)_size.x - ((float)charsize * 0.65 * (float)_text.size())) / 2.0);
    int textposy = _pos.y + (float)((float)_size.y) - (((float)charsize * 1.4));

    _core.drawRect(_pos, _size, _rectColor, 2, {25, 25, 25});
    _core.drawText(*_core.ressources.getFont("yoster"), _text, charsize, {textposx, textposy}, _textColor, 0, sf::Color::Black);
    if (_status == PRESSED) {
        _core.drawRect(_pos, _size, {0, 0, 0, 50}, 2, {25, 25, 25});
    }
}

void RectButton::draw(float mdr)
{
    int charsize = ((float)_size.y / mdr);
    int textposx = (float)(_pos.x) + (float)(((float)_size.x - ((float)charsize * 0.60 * (float)_text.size())) / 2.0);
    int textposy = _pos.y + (float)((float)_size.y) - (((float)charsize * 2.1));

    _core.drawRect(_pos, _size, _rectColor, 2, {25, 25, 25});
    _core.drawText(*_core.ressources.getFont("yoster"), _text, charsize, {textposx, textposy}, _textColor, 0, sf::Color::Black);
    if (_status == PRESSED) {
        _core.drawRect(_pos, _size, {0, 0, 0, 50}, 2, {25, 25, 25});
    }
}

void RectButton::computeStatus(void)
{
    _status = IDLE;
    if ((float)(_core.input.getMousePos().x) >= ((float)(_pos.x) * _core.resizefactor.x) &&
    (float)(_core.input.getMousePos().x) <= ((float)(_pos.x + _size.x) * _core.resizefactor.x)
    && (float)(_core.input.getMousePos().y) >= ((float)(_pos.y) * _core.resizefactor.y) &&
    (float)(_core.input.getMousePos().y) <= ((float)(_pos.y + _size.y) * _core.resizefactor.y)) {
        if (_core.input.isMouseButtonPressed(sf::Mouse::Left))
            _status = PRESSED;
        if (_core.input.isMouseButtonReleased(sf::Mouse::Left))
            _status = RELEASED;
    }
}

Button::ButtonStatus RectButton::getStatus() const
{
    return (_status);
}

void RectButton::setText(std::string &str)
{
    _text = str;
}