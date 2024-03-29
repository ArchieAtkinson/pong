#include <cstdio>
#include <fmt/format.h>
#include <chrono>
#include <array>

#include "debug_win.hpp"


DebugWin::DebugWin(Pos<int> origin, Size<int> size) : _origin(origin), _size(size)
{
}

void DebugWin::init()
{
    _win = newwin(_size.y, _size.x, _origin.y, _origin.x);
    drawBox();
}

void DebugWin::drawBox()
{
    chtype default_char = 0;
    box(_win, default_char, default_char);
    mvwprintw(_win, 0 , 2, "Logs");
    wrefresh(_win);
}