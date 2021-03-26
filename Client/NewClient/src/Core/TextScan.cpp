/*
** EPITECH PROJECT, 2020
** game-proto
** File description:
** TextScan
*/

#include "TextScan.hpp"

TextScan::TextScan(Core &core) : _core(core), _asking(false), _ended(false), _cursorpos(0)
{
    _str = "";
}

TextScan::~TextScan()
{
}

void TextScan::ask()
{
    _asking = true;
}

void TextScan::stopAsk()
{
    _asking = false;
}

void TextScan::reset()
{
    _str.clear();
    _asking = false;
    _ended = false;
}

void TextScan::update()
{
    if (!_core.input.isTextEntered() || !_asking)
        return;
    if (_core.input.getKeyEntered() == 13) {
        _asking = false;
        _ended = true;
        return;
    }
    if (_core.input.getKeyEntered() == 8) {
        if (_str.size()) {
            _str.pop_back();
            _cursorpos--;
        }
        return;
    }
    if (!std::isprint(_core.input.getKeyEntered()))
        return;
    _str.push_back(_core.input.getKeyEntered());
    _cursorpos++;
}

bool TextScan::getEnded() const
{
    return (_ended);
}

bool TextScan::getAsking() const
{
    return (_asking);
}

unsigned int TextScan::getCursorPos() const
{
    return (_cursorpos);
}

std::string TextScan::getStr() const
{
    return (_str);
}