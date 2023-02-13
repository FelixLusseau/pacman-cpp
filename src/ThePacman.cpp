
#include "../include/ThePacman.hpp"

ThePacman::ThePacman() : Character() {

    sprite_[0] = {18, 90, 16, 16};
    sprite_[1] = {34, 90, 14, 16};

    sprite_[2] = {48, 90, 16, 16};
    sprite_[3] = {64, 90, 12, 16};

    sprite_[4] = {108, 90, 16, 16};
    sprite_[5] = {124, 90, 20, 16};

    sprite_[6] = {76, 90, 16, 16};
    sprite_[7] = {92, 90, 16, 16};

    position_ = {34, 34, 32, 32};
}