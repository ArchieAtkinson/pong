#pragma once

#include <vector>

class KeyHold 
{
    public:
        explicit KeyHold(   int character,
                            std::size_t tick_threshold = default_tick_threshold);
        bool isHeld(int input);
        
    private:
        int _char; 
        std::size_t _tick_thresh;
        bool _active = false;
        std::size_t _count {0};
        static constexpr std::size_t default_tick_threshold = 10;
};