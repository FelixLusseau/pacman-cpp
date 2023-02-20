
#include "../include/ThePacman.hpp"

ThePacman::ThePacman() : Character() {
    /* right */
    sprite_[0] = {18, 90, 16, 16};
    sprite_[1] = {34, 90, 14, 16};
    /* left */
    sprite_[2] = {48, 90, 16, 16};
    sprite_[3] = {62, 90, 14, 16};
    /* up */
    sprite_[4] = {108, 90, 16, 16};
    sprite_[5] = {126, 94, 16, 12};
    /* down */
    sprite_[6] = {76, 90, 16, 16};
    sprite_[7] = {92, 94, 16, 12};

    cur_sprite_= {3, 90, 16, 16};

    position_ = {34, 34, 32, 32};
}

void ThePacman::deplacement(const Uint8 *keys, int animation,std::vector<std::vector<Tile>> map){
    int x=0;
    int y=0;

    if (keys[SDL_SCANCODE_RIGHT]) {
        cur_sprite_=sprite_[0+animation];
        x=2;
    }
    if (keys[SDL_SCANCODE_LEFT]) {
        cur_sprite_=sprite_[2+animation];
        x=-2;
    }
    if (keys[SDL_SCANCODE_DOWN]) {
        cur_sprite_=sprite_[4+animation];
        y=2;
    }
    if (keys[SDL_SCANCODE_UP]) {
        cur_sprite_=sprite_[6+animation];
        y=-2;
    }
    this->changePosition(position_.x+x,position_.y+y, map);

    std::cout<<position_.x<<" "<<position_.y<<std::endl;
}