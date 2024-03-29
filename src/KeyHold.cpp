#include "KeyHold.hpp"
#include "util.hpp"

KeyHold::KeyHold(int character, std::size_t tick_threshold) :
_char(character), _tick_thresh(tick_threshold)
{
    
}

bool KeyHold::isHeld(int input)
{
    if(input == _char)
    {
        _active = true;
        _count = 0;
        return true;
    }
    
    if(!_active)
    {
        return false;
    }

    _count++;

    if (_count < _tick_thresh)
    {
        return true;
    }
    else
    {
        _active = false;
        _count = 0;
        return false;
    }

    return false;
}