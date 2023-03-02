#include "../include/Dot.hpp"

Dot::Dot(int x, int y, TypeDot typeDot) {

    exist = true;
    type=typeDot;

    switch(type){
        case TypeDot::Simple:
            sprite_ = {3, 80, 4, 4};
            point = 10;
            break;
        case TypeDot::Big:
            sprite_ = {9, 79, 7, 7};
            point = 50;
            break;
    }

    position_ = {x, y, sprite_.w*4, sprite_.h*4};
};

int Dot::getEat(SDL_Rect *pac_position) {

    if (!exist) {
        return 0;
    }

    int score{0};

    float side = (float(pac_position->w) / 2);

    float origineX = float(pac_position->x) + float(pac_position->w) / 2;
    float origineY = float(pac_position->y) + float(pac_position->w) / 2;

    // float distance=sqrt( pow(float(position_.x)-origineX,2) + pow(float(position_.y)-origineY,2) );

    if (abs(origineX - position_.x) < side && abs(origineY - position_.y) < side) {
        exist = false;
        score = point;
        //std::cout << "get eaten!, +" << score << " x:" << position_.x << " y:" << position_.y << std::endl;
        //std::cout << "pacman x:" << origineX << " y:" << origineY << std::endl;
    }

    return score;
};