
#include "../include/Clyde.hpp"

Clyde::Clyde() : Ghost() {
    /* right */
    sprite_[0] = {3, 177, 16, 16};
    sprite_[1] = {20, 177, 16, 16};
    /* left */
    sprite_[2] = {36, 177, 16, 16};
    sprite_[3] = {53, 177, 16, 16};
    /* up */
    sprite_[4] = {71, 177, 16, 16};
    sprite_[5] = {88, 177, 16, 16};
    /* down */
    sprite_[6] = {105, 177, 16, 16};
    sprite_[7] = {122, 177, 16, 16};

    position_ = {34, 34, 32, 32}; // ici scale x2
}