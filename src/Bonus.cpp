#include "../include/Bonus.hpp"

Bonus::Bonus() {
    switch (Game::level) {
    case 1:
        type = TypeBonus::Cherry;
        point = 100;
        break;
    case 2:
        type = TypeBonus::Strawberry;
        point = 300;
        break;
    case 3:
    case 4:
        type = TypeBonus::Orange;
        point = 500;
        break;
    case 5:
    case 6:
        type = TypeBonus::Apple;
        point = 700;
        break;
    case 7:
    case 8:
        type = TypeBonus::Melon;
        point = 1000;
        break;
    case 9:
    case 10:
        type = TypeBonus::Galaxian;
        point = 2000;
        break;
    case 11:
    case 12:
        type = TypeBonus::Bell;
        point = 3000;
        break;
    case 13:
    case default:
        type = TypeBonus::Key;
        point = 5000;
        break;
    }
    exist = false;
    sprite_ = {0, 0, 16, 16};
    position_ = {0, 0, 16, 16};
}