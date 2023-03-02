
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

void Blinky::move(int animation, SDL_Rect *PacPosition ,std::vector<std::vector<Tile>> map, SDL_Rect bg){

    // tailles d'une case de la carte
    float tailleCaseX = float(bg.w) / float(map[0].size());
    float tailleCaseY = float(bg.h) / float(map.size());

    // taille de la case du sprite
    int tailleSprite = (position_.w / 2);

    // origine = centre de la case du sprite et pas son coin gauche
    int origineX = position_.x + tailleSprite;
    int origineY = position_.y + tailleSprite;

    // origine = centre de la case du sprite et pas son coin gauche
    int PacOrigineX = PacPosition->x + PacPosition->w/2;
    int PacOrigineY = PacPosition->y + PacPosition->h/2;

    int ligne=(int)(origineX/tailleCaseX);
    int colonne=(int)(origineY/tailleCaseY);

    std::vector<Tile> directions={map[colonne+1][ligne],
                                    map[colonne-1][ligne],
                                    map[colonne][ligne+1],
                                    map[colonne][ligne-1]};

    // bien aligné sur une case => est ce qu'on est sur une intersection?
    int rondeur{4};
    int intersection{0};

    int cornerX=static_cast<int>(position_.x+rondeur)/tailleCaseX;
    int cornerXX=static_cast<int>(position_.x+tailleSprite*2-rondeur)/tailleCaseX;
    int cornerY=static_cast<int>(position_.y+rondeur)/tailleCaseY;
    int cornerYY=static_cast<int>(position_.y+tailleSprite*2-rondeur)/tailleCaseY;
    
    if(cornerX==cornerXX && cornerY==cornerYY){
        for( int i{0}; i<4 ;i++){
            if(directions[i]!=Tile::Wall && directions[i]!=Tile::GhostHouseDoor){
                intersection++;
            }
        }
    }

    // on choisit une nouvelle direction si on est a une intersection (3 directions possible) ou si on a arrêté de bouger
    if( intersection >= 3 || prec_key== SDL_SCANCODE_UNKNOWN){  

        std::cout<<"choix direction"<<std::endl;

        float min{(float)bg.h};
        int best{5};

        for( int i{0}; i<4 ;i++){

            int nextX{0};
            int nextY{0};

            // on teste quelle direction est la meilleur
            if(directions[i]!=Tile::Wall && 
               directions[i]!=Tile::GhostHouseDoor ){
                switch(i){
                    case 0:
                        nextX=origineX;
                        nextY=origineY+tailleSprite*2;
                        break;
                    case 1:
                        nextX=origineX;
                        nextY=origineY-tailleSprite*2;
                        break;
                    case 2:
                        nextX=origineX+tailleSprite*2;
                        nextY=origineY;
                        break;
                    case 3:
                        nextX=origineX-tailleSprite*2;
                        nextY=origineY;
                        break;
                }
                
                float dist=sqrt( pow(float(nextX-PacOrigineX),2)+pow(float(nextY-PacOrigineY),2));
                if(dist < min){
                    min=dist;
                    best=i;
                }
            }
        }
        switch(best){
            case 0:
                std::cout<<"best:down"<<std::endl;
                prec_key=SDL_SCANCODE_DOWN;
                break;
            case 1:
                std::cout<<"best:up"<<std::endl;
                prec_key=SDL_SCANCODE_UP;
                break;
            case 2:
                std::cout<<"best:right"<<std::endl;
                prec_key=SDL_SCANCODE_RIGHT;
                break;
            case 3:
                std::cout<<"best:left"<<std::endl;
                prec_key=SDL_SCANCODE_LEFT;
                break;
        }
    }
    this->dontStopMoving(animation, map,bg);
    

}