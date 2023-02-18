
#include "../include/Pinky.hpp"

Pinky::Pinky() : Ghost() {
    /* right */
    sprite_[0] = {3, 141, 16, 16};
    sprite_[1] = {20, 141, 16, 16};
    /* left */
    sprite_[2] = {36, 141, 16, 16};
    sprite_[3] = {53, 141, 16, 16};
    /* up */
    sprite_[4] = {71, 141, 16, 16};
    sprite_[5] = {88, 141, 16, 16};
    /* down */
    sprite_[6] = {105, 141, 16, 16};
    sprite_[7] = {122, 141, 16, 16};

    position_ = {34, 34, 32, 32}; // ici scale x2
}