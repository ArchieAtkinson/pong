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

void DebugWin::print2(const char *fmt, ...)
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* timeInfo = std::localtime(&currentTime);

    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;

    std::ostringstream time_oss;
    time_oss << std::put_time(timeInfo, "%H:%M:%S");
    time_oss << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
    std::string timeStr = time_oss.str();

    va_list args;
    va_start(args, fmt);

    std::ostringstream fmt_oss;
    const int bufferSize = 256;
    std::array<char,1024> buffer{};

    vsnprintf(buffer.data(), bufferSize, fmt, args);
    fmt_oss << buffer.data();

    va_end(args);
    std::string fmtStr = fmt_oss.str();

    std::string logMessage = "[" + timeStr + "] " + fmtStr;

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
    
    for(std::size_t i = 0; i < _logs.size(); i++)
    {
        mvwprintw(_win, i + 1 , 1, "%s", _logs.at(i).c_str());
    }
    wrefresh(_win);
}