
#include "../include/Blinky.hpp"

Blinky::Blinky(int PixelX, int PixelY) : Ghost() {
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

    position_ = {10*PixelX+4, 10*PixelY+4, 32, 32}; // ici scale x2

    cur_sprite_=sprite_[0];

    prec_key=SDL_SCANCODE_RIGHT;
}

void Blinky::chase(int animation, ThePacman *pacman ,std::vector<std::vector<Tile>> map, SDL_Rect bg){
    SDL_Rect *PacPosition=pacman->getPosition();

    // tailles d'une case de la carte
    float tailleCaseX = float(bg.w) / float(map[0].size());
    float tailleCaseY = float(bg.h) / float(map.size());

    // taille de la case du sprite
    int size = (position_.w );

    // origine = centre de la case du sprite et pas son coin gauche
    int origineX = position_.x + size/2;
    int origineY = position_.y + size/2;

    int ligne=static_cast<int>(origineX/tailleCaseX);
    int colonne=static_cast<int>(origineY/tailleCaseY);

    std::vector<Tile> directions={map[colonne+1][ligne],
                                    map[colonne-1][ligne],
                                    map[colonne][ligne+1],
                                    map[colonne][ligne-1]};

    bool inter{intersection(tailleCaseX,tailleCaseY,directions) };

    // on choisit une nouvelle direction si on est a une intersection (3 directions possible) ou si on a arrêté de bouger
    if( inter || prec_key== SDL_SCANCODE_UNKNOWN){
        shortestPath(PacPosition,directions,map, bg);
    }
    this->dontStopMoving(animation, map,bg);
    

}