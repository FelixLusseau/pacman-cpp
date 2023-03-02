#include "../include/Ghost.hpp"

Ghost::Ghost() : Character() {}


void Ghost::dontStopMoving(int animation, std::vector<std::vector<Tile>> map,SDL_Rect bg){

    SDL_Rect sp = cur_sprite_;

    int mv_x{0};
    int mv_y{0};

    switch(prec_key){
        case SDL_SCANCODE_RIGHT:
            cur_sprite_ = sprite_[0 + animation];
            mv_x = 1;
            break;
        case SDL_SCANCODE_LEFT:
            cur_sprite_ = sprite_[2 + animation];
            mv_x = -1;
            break;
        case SDL_SCANCODE_UP:
            cur_sprite_ = sprite_[4 + animation];
            mv_y = -1;
            break;
        case SDL_SCANCODE_DOWN:
            cur_sprite_ = sprite_[6 + animation];
            mv_y = 1;
            break;
    }

    this->changePosition(position_.x + mv_x, position_.y + mv_y, map, bg);

}