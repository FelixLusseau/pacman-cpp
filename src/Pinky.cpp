
#include "../include/Pinky.hpp"

Pinky::Pinky(int PixelX, int PixelY) : Ghost() {
    /* right */
    sprite_[0] = {3, 141, 16, 16};
    sprite_[1] = {20, 141, 16, 16};
    /* left */
    sprite_[2] = {36, 141, 16, 16};
    sprite_[3] = {53, 141, 16, 16};
    /* up */
    sprite_[4] = {71, 141, 16, 16};
    sprite_[5] = {88, 141, 16, 16};
    /* down */
    sprite_[6] = {105, 141, 16, 16};
    sprite_[7] = {122, 141, 16, 16};

    position_ = {10 * PixelX, 13 * PixelY, 32, 32};      // ici scale x2
    init_position_ = {10 * PixelX, 13 * PixelY, 32, 32}; // ici scale x2
    prec_key = SDL_SCANCODE_UP;

    corner_ = {PixelX * 2, -PixelY * 2, PixelX, PixelY};
}

void Pinky::chase(const std::unique_ptr<ThePacman> &pacman, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg) {

    SDL_Rect PacPosition = pacman->getPosition();

    // tailles d'une case de la carte
    int tailleCaseX{static_cast<int>(bg.w / map[0].size())};
    int tailleCaseY{static_cast<int>(bg.h / map.size())};

    // taille de la case du sprite
    int size{(position_.w) / 2};

    // origine = centre de la case du sprite et pas son coin gauche
    // int origineX{position_.x + size};
    // int origineY{position_.y + size};

    // int ligne{origineX / tailleCaseX};
    // int colonne{origineY / tailleCaseY};

    // pinky cherches à aller devant pacman
    SDL_Scancode pacMove{pacman->get_key()};
    int coeff{4}; // nombre de case devant pacman
    SDL_Rect Goal{PacPosition.x + size, PacPosition.y + size, tailleCaseX, tailleCaseY};

    int caseT{tailleCaseX};

    switch (pacMove) {
    case SDL_SCANCODE_RIGHT:
        Goal.x += (caseT * coeff);
        break;
    case SDL_SCANCODE_LEFT:
        Goal.x += (-caseT * coeff);
        break;
    case SDL_SCANCODE_UP:
        Goal.y += (-caseT * coeff);
        break;
    case SDL_SCANCODE_DOWN:
        Goal.y += (caseT * coeff);
        break;
    default:
        break;
    }

    goal_.x = Goal.x;
    goal_.y = Goal.y;
    goal_.w = Goal.w;
    goal_.h = Goal.h;
}