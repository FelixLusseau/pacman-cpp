
#include "../include/Blinky.hpp"

Blinky::Blinky() : Ghost() {
    /* right */
    sprite_[0] = {3, 123, 16, 16};
    sprite_[1] = {20, 123, 16, 16};
    /* left */
    sprite_[2] = {36, 123, 16, 16};
    sprite_[3] = {53, 123, 16, 16};
    /* up */
    sprite_[4] = {71, 123, 16, 16};
    sprite_[5] = {88, 123, 16, 16};
    /* down */
    sprite_[6] = {105, 123, 16, 16};
    sprite_[7] = {122, 123, 16, 16};

    position_ = {34, 34, 32, 32}; // ici scale x2
}