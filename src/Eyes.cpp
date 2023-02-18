
#include "../include/Eyes.hpp"

Eyes::Eyes() : Ghost() {
    /* right */
    sprite_[0] = {71, 195, 16, 16};
    /* left */
    sprite_[2] = {88, 195, 16, 16};
    /* up */
    sprite_[4] = {105, 195, 16, 16};
    /* down */
    sprite_[6] = {122, 195, 16, 16};

    for (int i = 1; i < 8; i += 2) {
        sprite_[i] = sprite_[i - 1];
    }

    position_ = {34, 34, 32, 32}; // ici scale x2
}