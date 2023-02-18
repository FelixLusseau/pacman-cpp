
#include "../include/Inky.hpp"

Inky::Inky() : Ghost() {
    /* right */
    sprite_[0] = {3, 159, 16, 16};
    sprite_[1] = {20, 159, 16, 16};
    /* left */
    sprite_[2] = {36, 159, 16, 16};
    sprite_[3] = {53, 159, 16, 16};
    /* up */
    sprite_[4] = {71, 159, 16, 16};
    sprite_[5] = {88, 159, 16, 16};
    /* down */
    sprite_[6] = {105, 159, 16, 16};
    sprite_[7] = {122, 159, 16, 16};

    position_ = {34, 34, 32, 32}; // ici scale x2
}