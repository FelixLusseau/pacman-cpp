
#include "Blinky.hpp"

Blinky::Blinky():Ghost(){
    sprite_[0] = {3, 123, 16, 16};
    sprite_[1] = {19, 123, 16, 16};
    sprite_[2] = {37, 123, 16, 16};
    sprite_[3] = {53, 123, 16, 16};
    sprite_[4] = {105, 123, 16, 16};
    sprite_[5] = {121, 123, 16, 16};
    sprite_[6] = {71, 123, 16, 16};
    sprite_[7] = {87, 123, 16, 16};
    position_ = {34, 34, 32, 32}; // ici scale x2
}