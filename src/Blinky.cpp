
#include "../include/Blinky.hpp"

Blinky::Blinky(const int PixelX, const int PixelY) : Ghost() {
    /* right */
    sprite_[0] = {3, 123, 16, 16};
    sprite_[1] = {20, 123, 16, 16};
    /* left */
    sprite_[2] = {36, 123, 16, 16};
    sprite_[3] = {53, 123, 16, 16};
    /* up */
    sprite_[4] = {71, 123, 16, 16};
    sprite_[5] = {88, 123, 16, 16};
    /* down */
    sprite_[6] = {105, 123, 16, 16};
    sprite_[7] = {122, 123, 16, 16};

    position_ = {10 * PixelX, 10 * PixelY, 32, 32}; // scale x2
    init_position_ = {10 * PixelX, 10 * PixelY, 32, 32};

    corner_ = {PixelX * 17, -PixelY, PixelX, PixelY};
    out_jail_ = true;
}

void Blinky::chase(const std::unique_ptr<ThePacman> &pacman, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg) {
    (void)map;
    (void)bg;
    SDL_Rect Goal = pacman->getPosition();
    goal_.x = Goal.x;
    goal_.y = Goal.y;
    goal_.w = Goal.w;
    goal_.h = Goal.h;
}