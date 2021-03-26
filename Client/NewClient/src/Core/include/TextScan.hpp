/*
** EPITECH PROJECT, 2020
** game-proto
** File description:
** TextScan
*/

#pragma once

#include "Core.hpp"

class TextScan {
    public:
        TextScan(Core &core);
        ~TextScan();
        virtual void ask();
        virtual void stopAsk();
        virtual void reset();
        virtual void update();
        virtual bool getEnded() const;
        virtual bool getAsking() const;
        virtual unsigned int getCursorPos() const;
        virtual std::string getStr() const;

    protected:
        Core &_core;
        bool _asking;
        bool _ended;
        unsigned int _cursorpos;
        std::string _str;
};
