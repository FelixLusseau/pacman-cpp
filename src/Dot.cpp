#include "../include/Dot.hpp"
#include "../include/Game.hpp"
#include "../include/Ghost.hpp"

int Dot::nb_dot_tot{0};
int Dot::nb_dot_eaten{0};

Dot::Dot(const int x, const int y, const TypeDot typeDot) {

    exist_ = true;
    type_ = typeDot;

    switch (type_) {
    case TypeDot::Simple:
        sprite_ = {3, 80, 4, 4};
        points_ = 10;
        break;
    case TypeDot::Big:
        sprite_ = {9, 79, 7, 7};
        points_ = 50;
        break;
    }

    position_ = {x, y, sprite_.w * 4, sprite_.h * 4};

    nb_dot_tot++;
};

int Dot::getEat(const SDL_Rect &pac_position) {

    if (!exist_) {
        return 0;
    }

    int score{0};

    float origineX{static_cast<float>(pac_position.x + (pac_position.w / 2))};
    float origineY{static_cast<float>(pac_position.y + (pac_position.h / 2))};

    float dotOrigineX{static_cast<float>(position_.x + (pac_position.w / 2))};
    float dotOrigineY{static_cast<float>(position_.y + (pac_position.w / 2))};

    float distance = sqrt(pow(dotOrigineX - origineX, 2) + pow(dotOrigineY - origineY, 2));

    if (distance < (pac_position.w / 2.25)) {
        exist_ = false;
        score = points_;
        if (type_ == TypeDot::Big) {
            Ghost::idle = true;
            Game::timer_begin = clock();
        }
        nb_dot_eaten++;
    }

    if (nb_dot_eaten == nb_dot_tot) {
        Game::next_level = true;
    }

    return score;
};