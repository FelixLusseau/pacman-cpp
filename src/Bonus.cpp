#include "../include/Bonus.hpp"
#include "../include/Game.hpp"

Bonus::Bonus() {
    hundred_sprite_ = {178, 132, 15, 8};
    three_hundreds_sprite_ = {178, 141, 15, 8};
    five_hundreds_sprite_ = {178, 150, 15, 8};
    seven_hundreds_sprite_ = {178, 159, 15, 8};
    one_thousand_sprite_ = {176, 168, 17, 8};
    two_thousands_sprite_ = {176, 177, 17, 8};
    three_thousands_sprite_ = {176, 186, 17, 8};
    five_thousands_sprite_ = {176, 195, 17, 8};

    cherry_sprite_ = {289, 257, 13, 13};
    strawberry_sprite_ = {306, 257, 13, 13};
    orange_sprite_ = {321, 257, 13, 13};
    apple_sprite_ = {337, 257, 13, 13};
    melon_sprite_ = {354, 257, 13, 13};
    galaxian_sprite_ = {370, 257, 13, 13};
    bell_sprite_ = {386, 257, 13, 13};
    key_sprite_ = {404, 257, 13, 13};

    switch (Game::level) {
    case 1:
        type = TypeBonus::Cherry;
        point = 100;
        sprite_ = cherry_sprite_;
        sprite_points_ = hundred_sprite_;
        break;
    case 2:
        type = TypeBonus::Strawberry;
        point = 300;
        sprite_ = strawberry_sprite_;
        sprite_points_ = three_hundreds_sprite_;
        break;
    case 3:
    case 4:
        type = TypeBonus::Orange;
        point = 500;
        sprite_ = orange_sprite_;
        sprite_points_ = five_hundreds_sprite_;
        break;
    case 5:
    case 6:
        type = TypeBonus::Apple;
        point = 700;
        sprite_ = apple_sprite_;
        sprite_points_ = seven_hundreds_sprite_;
        break;
    case 7:
    case 8:
        type = TypeBonus::Melon;
        point = 1000;
        sprite_ = melon_sprite_;
        sprite_points_ = one_thousand_sprite_;
        break;
    case 9:
    case 10:
        type = TypeBonus::Galaxian;
        point = 2000;
        sprite_ = galaxian_sprite_;
        sprite_points_ = two_thousands_sprite_;
        break;
    case 11:
    case 12:
        type = TypeBonus::Bell;
        point = 3000;
        sprite_ = bell_sprite_;
        sprite_points_ = three_thousands_sprite_;
        break;
    case 13:
    default:
        type = TypeBonus::Key;
        point = 5000;
        sprite_ = key_sprite_;
        sprite_points_ = five_thousands_sprite_;
        break;
    }
    exist = false;
    position_ = {315, 475, 30, 30};
}