#include "../include/Character.hpp"

Character::Character(){};

void Character::changePosition(int x, int y) {
    position_.x = x;
    position_.y = y;
}