
#include "../include/BlueGhost.hpp"

BlueGhost::BlueGhost() : Ghost() {
    sprite_[0] = {3, 195, 16, 16};
    sprite_[1] = {20, 195, 16, 16};

    for (int i = 2; i < 8; i += 2) {
        sprite_[i] = sprite_[0];
        sprite_[i + 1] = sprite_[1];
    }

    position_ = {34, 34, 32, 32}; // ici scale x2
}