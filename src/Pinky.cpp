
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

    position_ = {10*PixelX+4, 10*PixelY+4, 32, 32}; // ici scale x2
}

void Pinky::chase(int animation, ThePacman *pacman ,std::vector<std::vector<Tile>> map, SDL_Rect bg){

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

    //pinky cherches à aller devant pacman
    SDL_Scancode pacMove=pacman->get_key();
    int coeff{4};
    SDL_Rect Goal={PacPosition->x+(size/2),PacPosition->y+(size/2),0,0};


    int caseT=static_cast<int>(tailleCaseX);

    std::cout<<caseT*coeff<<std::endl;
    std::cout<<Goal.y<<std::endl;
    std::cout<<PacPosition->y<<std::endl;

    switch(pacMove){
        case SDL_SCANCODE_RIGHT:
            Goal.x+=(caseT*coeff);
            break;
        case SDL_SCANCODE_LEFT:
            Goal.x+=(-caseT*coeff);
            break;
        case SDL_SCANCODE_UP:
            Goal.y+=(-caseT*coeff);
            break;
        case SDL_SCANCODE_DOWN:
            Goal.y+=(caseT*coeff);
            break;
    
    }

    // on choisit une nouvelle direction si on est a une intersection (3 directions possible) ou si on a arrêté de bouger
    if( inter || prec_key== SDL_SCANCODE_UNKNOWN){
            
        if(idle){
            Goal=position_;
        }else if(eyes){
            Goal=jail_position_;

        }
        choosePath(&Goal,directions,map, bg);
    }
    this->dontStopMoving(animation, map,bg);
    


}