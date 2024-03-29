// #define _XOPEN_SOURCE_EXTENDED // Required for Unicode

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <clocale>

#include <memory>
#include <string>
#include <thread>
#include <queue>
#include <numeric>

#include <curses.h>
#include <panel.h>

#include "KeyHold.hpp"
#include "debug_win.hpp"
#include "util.hpp"
#include "Paddle.hpp"



struct pos_t 
{
    float y;
    float x;
};

constexpr int offset_y = 1;

struct game_t 
{
    std::string name;
    pos_t player_one_pos;
    pos_t player_two_pos;
    WINDOW * display_win;
    WINDOW * game_win;
    DebugWin *logs;
    Paddle paddle = Paddle({win_x/2, offset_y}, {8, 1}, 200.0);
};

DebugWin LOG({win_x + 2,0}, {50, win_y + 2});

constexpr int paddle_y = 4;

double_sec frameTime;

std::deque<double_sec> fps_avg;
constexpr std::size_t avg_n = 240;

double_sec avg_fps(double_sec latestValue){
    if(fps_avg.size() == avg_n)
    {
        fps_avg.pop_back();
    }
    fps_avg.push_front(latestValue);

    return std::accumulate(fps_avg.begin(), fps_avg.end(), double_sec{0}) / fps_avg.size();

}

void display_border(game_t & context)
{
    box(context.display_win, 0, 0);
    int x_pos = win_x/2 - context.name.length()/2;

    mvwprintw(context.display_win, 0, 0, "%.0ffps", 1/avg_fps(frameTime).count());

    wattron(context.display_win, A_BOLD);
    mvwprintw(context.display_win, 0, x_pos, "%s", context.name.c_str());
    wattroff(context.display_win, A_BOLD);
}


int init(game_t & context)
{
    setlocale(LC_ALL, "en_US.UTF-8");
    assert(initscr() != nullptr);
    assert(cbreak() != ERR);
    assert(noecho() != ERR);
    
    assert(nodelay(stdscr, TRUE) != ERR);
    assert(curs_set(0) != ERR);

    context.display_win = newwin(win_y + 2, win_x + 2, 0, 0); // Allows border
    context.game_win = newwin(win_y, win_x, 1, 1);

    assert(keypad(context.game_win, TRUE) != ERR);
    assert(nodelay(context.game_win, TRUE) != ERR);

    LOG.init();

    return 0;
}

int update(game_t &context, double_sec dt)
{
    static KeyHold key_up(KEY_UP);
    static KeyHold key_down(KEY_DOWN);
    int c = wgetch(context.game_win);

    context.paddle.update(dt, c);
        
    return 0;
}

int draw(game_t &context)
{
    erase();

    display_border(context);
 
    context.paddle.draw(context.game_win);

    wnoutrefresh(context.display_win);
    wnoutrefresh(context.game_win);
    doupdate();

    return 0;
}

int main()
{       
    game_t context {"Pogo"};

    init(context);

    double_sec t {0};
    constexpr double_sec dt = 0.001s;

    double_time_point currentTime = Time::now(); 
    double_sec accumulator {0};

    double_sec previousState;
    double_sec currentState;

    constexpr double_sec frameLimit(1.0f/120.0f);
    while(true)
    {
        double_time_point newTime = Time::now(); 
        frameTime = newTime - currentTime;  
        accumulator += frameTime;
        currentTime = newTime; 

        while ( accumulator >= dt )
        {
            previousState = currentState;
            update(context, dt);
            // uppdate( currentState, t, dt );
            t += dt;
            accumulator -= dt;
        }

        draw(context);

        auto currentFrameDuration = Time::now() - newTime;
        if(currentFrameDuration  < frameLimit){
            std::this_thread::sleep_for(frameLimit - currentFrameDuration); 

        } 
    }

    endwin();
    return 0;
}




