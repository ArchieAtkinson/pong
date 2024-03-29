#pragma once

#include <chrono>

#include "curses.h"

template<typename T>
struct Pos{
    T x;
    T y;
};

template<typename T>
struct Size{
    T x;
    T y;
};

using Time = std::chrono::steady_clock;
using ms = std::chrono::milliseconds;
using double_sec = std::chrono::duration<double>;
using double_time_point = std::chrono::time_point<Time, double_sec>;
using namespace std::literals;

constexpr int win_y = 25;
constexpr int win_x = 75;