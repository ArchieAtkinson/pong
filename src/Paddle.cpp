#include <cmath>
#include <type_traits>

#include "curses.h"

#include "debug_win.hpp"

#include "Paddle.hpp"

Paddle::Paddle(Pos<float> starting_pos, Size<float> size, float speed) :
_pos{starting_pos}, _size{size}, _speed{speed}
{
}

void Paddle::update(double_sec dt, int input_c)
{
    if (_key_left.isHeld(input_c))
    {
        float next_pos = _pos.x - (_speed * dt.count());
        if(next_pos - _size.x/2 >= 0)
        {
            _pos.x = next_pos;
        }  
        else
        {
            _pos.x = _size.x/2;
        }
    }

    if (_key_right.isHeld(input_c))
    {
        float next_pos = _pos.x + (_speed * dt.count());
        
        if(next_pos + _size.x/2  < win_x)
        {
            _pos.x = next_pos;
        }
        else
        {
            _pos.x = win_x - _size.x/2;
        }
    }

    LOG.print("{}", _pos.x);
}

void Paddle::draw(WINDOW * win)
{
    for (int i = 0; i < win_x; i++)
    {
        mvwaddch(win, _pos.y, i, ' ');
    }

    for(int i = 0; i < _size.x; i++)
    {
        mvwaddwstr(win, _pos.y, std::floor(_pos.x - _size.x/2 + i),  _blocks.at(1).data());
    }
}