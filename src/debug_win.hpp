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

#include "util.hpp"

class DebugWin;
extern DebugWin LOG;

class DebugWin
{
    public:
        DebugWin(Pos<int> orign, Size<int> size);
        template <typename... Args>
        void print(std::string_view fmt, Args&&... args)
        {
            auto now = std::chrono::system_clock::now();
            std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
            std::tm* timeInfo = std::localtime(&currentTime);

            auto duration = now.time_since_epoch();
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;

            std::ostringstream oss;
            oss << std::put_time(timeInfo, "%H:%M:%S");
            oss << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
            std::string timeStr = oss.str();


            std::string message = fmt::vformat(fmt, fmt::make_format_args(args...));
            fmt::vformat(message, fmt::make_format_args(message));

            std::string logMessage = fmt::format("[{}] {}", timeStr, message);
            fmt::vformat(logMessage, fmt::make_format_args(logMessage));

            if (logMessage.length() > _size.x - 2)
            {
                logMessage = logMessage.substr(0, _size.x - 5);
                logMessage += "...";
            }
        

            _logs.push_front(logMessage);
            if(_logs.size() == static_cast<std::size_t>(_size.y) - 1)
            {
                _logs.pop_back();
            }
            
            std::string filler(_size.x - 2,' ');
            // werase(_win);

            // drawBox();
            for(std::size_t i = 0; i < _logs.size(); i++)
            {   
                mvwprintw(_win, i + 1 , 1, "%s", filler.c_str());
                mvwprintw(_win, i + 1 , 1, "%s", _logs.at(i).c_str());
            }
            wrefresh(_win);
        }
        void init();
        void print2(const char *fmt, ...);
    private:
        void drawBox();
        WINDOW * _win = nullptr;
        std::deque<std::string> _logs;
        Pos<int> _origin {};
        Size<int> _size {};
};

