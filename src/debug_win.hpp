#pragma once

#include <string>
#include <deque>
#include <cstdio>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdarg>

#include <curses.h>
#include <fmt/format.h>
#include <fmt/chrono.h>

#include "util.hpp"

class DebugWin;
extern DebugWin LOG;

class DebugWin
{
    public:
        DebugWin(Pos<int> orign, Size<int> size);
        void init();
        template <typename... Args>
        void print(fmt::format_string<Args...> fstring, Args&&... args)
        {
            std::string message = fmt::format(fstring, std::forward<Args>(args)...);
            
            auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
            auto now_ms = std::chrono::floor<std::chrono::milliseconds>(now);

            std::string log_message = fmt::format("[{:%H:%M:%S}] {}", now_ms, message);

            if (log_message.length() > _size.x - 2)
            {
                log_message = log_message.substr(0, _size.x - 5);
                log_message += "...";
            }
        
            _logs.push_front(log_message);
            if(_logs.size() == static_cast<std::size_t>(_size.y) - 1)
            {
                _logs.pop_back();
            }
            
            std::string filler(_size.x - 2,' ');

            for(std::size_t i = 0; i < _logs.size(); i++)
            {   
                mvwprintw(_win, i + 1 , 1, "%s", filler.c_str());
                mvwprintw(_win, i + 1 , 1, "%s", _logs.at(i).c_str());
            }
            wrefresh(_win);
        }
    private:
        void drawBox();
        WINDOW * _win = nullptr;
        std::deque<std::string> _logs;
        Pos<int> _origin {};
        Size<int> _size {};
};

