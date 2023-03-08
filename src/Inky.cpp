
#include "../include/Inky.hpp"

Inky::Inky() : Ghost() {
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

    position_ = {34, 34, 32, 32}; // ici scale x2
}

void Inky::chase(int animation, ThePacman *pacman ,std::vector<std::vector<Tile>> map, SDL_Rect bg){
    
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
            
        if(idle){
            PacPosition=&position_;
        }else if(eyes){
            PacPosition=&jail_position_;

        }

        choosePath(PacPosition,directions,map, bg);
    }
    this->dontStopMoving(animation, map,bg);
    


}