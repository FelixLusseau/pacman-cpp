
#include "../include/Inky.hpp"

Inky::Inky(int PixelX, int PixelY) : Ghost() {
    /* right */
    sprite_[0] = {3, 159, 16, 16};
    sprite_[1] = {20, 159, 16, 16};
    /* left */
    sprite_[2] = {36, 159, 16, 16};
    sprite_[3] = {53, 159, 16, 16};
    /* up */
    sprite_[4] = {71, 159, 16, 16};
    sprite_[5] = {88, 159, 16, 16};
    /* down */
    sprite_[6] = {105, 159, 16, 16};
    sprite_[7] = {122, 159, 16, 16};

    position_ = {9 * PixelX , 13 * PixelY , 32, 32};      // ici scale x2
    init_position_ = {9 * PixelX , 13 * PixelY, 32, 32}; // ici scale x2
    prec_key=SDL_SCANCODE_UP;

    corner_={PixelX*18,PixelY*22,PixelX,PixelY};

}

Inky::Inky(int PixelX, int PixelY,Ghost *blinky) : Ghost(){
    blinky_=blinky;

    /* right */
    sprite_[0] = {3, 159, 16, 16};
    sprite_[1] = {20, 159, 16, 16};
    /* left */
    sprite_[2] = {36, 159, 16, 16};
    sprite_[3] = {53, 159, 16, 16};
    /* up */
    sprite_[4] = {71, 159, 16, 16};
    sprite_[5] = {88, 159, 16, 16};
    /* down */
    sprite_[6] = {105, 159, 16, 16};
    sprite_[7] = {122, 159, 16, 16};

    position_ = {9 * PixelX , 13 * PixelY , 32, 32};      // ici scale x2
    init_position_ = {9 * PixelX , 13 * PixelY, 32, 32}; // ici scale x2
    prec_key=SDL_SCANCODE_UP;

    corner_={PixelX*18,PixelY*22,PixelX,PixelY};
}

void Inky::chase(int animation, ThePacman *pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg) {

    SDL_Rect *PacPosition = pacman->getPosition();
    SDL_Rect *BlyPosition = blinky_->getPosition();

    // tailles d'une case de la carte
    int tailleCaseX = bg.w / map[0].size();
    int tailleCaseY = bg.h/ map.size();

    // taille de la case du sprite
    int size = (position_.w)/2;

    // origine = centre de la case du sprite et pas son coin gauche
    int origineX = position_.x + size ;
    int origineY = position_.y + size ;


    // pinky cherches à aller devant pacman
    SDL_Scancode pacMove = pacman->get_key();
    int coeff{4};// nombre de case devant pacman
    SDL_Rect Goal = {PacPosition->x + size, PacPosition->y + size, tailleCaseX, tailleCaseY};

    int caseT = tailleCaseX;

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
    }

    goal_.x=((BlyPosition->x/ tailleCaseX)+((Goal.x / tailleCaseX)-(BlyPosition->x/ tailleCaseX)))*tailleCaseX;
    goal_.y=((BlyPosition->y/ tailleCaseY)+((Goal.y / tailleCaseY)-(BlyPosition->y/ tailleCaseY)))*tailleCaseY;
    goal_.w=Goal.w;
    goal_.h=Goal.h;
}