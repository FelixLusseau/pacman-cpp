
#include "../include/Clyde.hpp"

Clyde::Clyde(int PixelX, int PixelY) : Ghost() {
    /* right */
    sprite_[0] = {3, 177, 16, 16};
    sprite_[1] = {20, 177, 16, 16};
    /* left */
    sprite_[2] = {36, 177, 16, 16};
    sprite_[3] = {53, 177, 16, 16};
    /* up */
    sprite_[4] = {71, 177, 16, 16};
    sprite_[5] = {88, 177, 16, 16};
    /* down */
    sprite_[6] = {105, 177, 16, 16};
    sprite_[7] = {122, 177, 16, 16};

    position_ = {11 * PixelX, 13 * PixelY, 32, 32};      // ici scale x2
    init_position_ = {11 * PixelX, 13 * PixelY, 32, 32}; // ici scale x2
    prec_key = SDL_SCANCODE_UP;

    corner_ = {PixelX * 1, PixelY * 27, PixelX, PixelY};
    status_ = Status::stay_jail;
}

void Clyde::chase(std::unique_ptr<ThePacman> &pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg) {

    SDL_Rect *Goal{pacman->getPosition()};

    // tailles d'une case de la carte
    float tailleCaseX{float(bg.w) / float(map[0].size())};
    float tailleCaseY{float(bg.h) / float(map.size())};

    int dist_min{static_cast<int>(tailleCaseX * 4)};
    int dist_pac{static_cast<int>(sqrt(pow(float(position_.x - Goal->x), 2) + pow(float(position_.y - Goal->y), 2)))};

    if (dist_pac <= dist_min) {
        Goal = &corner_;
    }

    goal_.x = Goal->x;
    goal_.y = Goal->y;
    goal_.w = Goal->w;
    goal_.h = Goal->h;
}