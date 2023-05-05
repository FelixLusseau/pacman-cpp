#include "../include/Bonus.hpp"
#include "../include/Game.hpp"

Bonus::Bonus() {
    bonus_score_timer = 0;

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
        points = 100;
        sprite_ = cherry_sprite_;
        sprite_points_ = hundred_sprite_;
        break;
    case 2:
        type = TypeBonus::Strawberry;
        points = 300;
        sprite_ = strawberry_sprite_;
        sprite_points_ = three_hundreds_sprite_;
        break;
    case 3:
    case 4:
        type = TypeBonus::Orange;
        points = 500;
        sprite_ = orange_sprite_;
        sprite_points_ = five_hundreds_sprite_;
        break;
    case 5:
    case 6:
        type = TypeBonus::Apple;
        points = 700;
        sprite_ = apple_sprite_;
        sprite_points_ = seven_hundreds_sprite_;
        break;
    case 7:
    case 8:
        type = TypeBonus::Melon;
        points = 1000;
        sprite_ = melon_sprite_;
        sprite_points_ = one_thousand_sprite_;
        break;
    case 9:
    case 10:
        type = TypeBonus::Galaxian;
        points = 2000;
        sprite_ = galaxian_sprite_;
        sprite_points_ = two_thousands_sprite_;
        break;
    case 11:
    case 12:
        type = TypeBonus::Bell;
        points = 3000;
        sprite_ = bell_sprite_;
        sprite_points_ = three_thousands_sprite_;
        break;
    case 13:
    default:
        type = TypeBonus::Key;
        points = 5000;
        sprite_ = key_sprite_;
        sprite_points_ = five_thousands_sprite_;
        break;
    }
    exist = false;
    position_ = {315, 477, 30, 30};
}

int Bonus::getEat(SDL_Rect *pac_position) {

    if (!exist) {
        return 0;
    }

    int score{0};

    float origineX{float(pac_position->x + (pac_position->w / 2))};
    float origineY{float(pac_position->y + (pac_position->h / 2))};

    float bonusOrigineX{float(position_.x + (pac_position->w / 2))};
    float bonusOrigineY{float(position_.y + (pac_position->w / 2))};

    float distance = sqrt(pow(bonusOrigineX - origineX, 2) + pow(bonusOrigineY - origineY, 2));

    if (distance < (pac_position->w / 2.25)) {
        bonus_score_timer++;
        exist = false;
        score = points;
    }
    // std::cout << score << std::endl;

    return score;
};