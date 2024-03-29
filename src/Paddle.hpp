#pragma once

#include <array>

#include <curses.h>

#include "util.hpp"
#include "KeyHold.hpp"

using widec = std::array<const wchar_t,2>;

class Paddle 
{
    public:
        Paddle(Pos<float> starting_pos, Size<float> size, float speed);
        void update(double_sec dt,  int input_c);
        void draw(WINDOW * win);
    private:
        Pos<float> _pos;
        Size<float> _size;
        float _speed;
        KeyHold _key_left = KeyHold(KEY_LEFT);
        KeyHold _key_right = KeyHold(KEY_RIGHT);
        static constexpr std::array<widec,3> _blocks = 
        {
            L"▐",
            L"█",
            L"▌",
        };
}; 