#include "../include/Ghost.hpp"

Ghost::Ghost() : Character() {}


void Ghost::dontStopMoving(int animation, std::vector<std::vector<Tile>> map,SDL_Rect bg){

    SDL_Rect sp = cur_sprite_;

    int mv_x{0};
    int mv_y{0};

    switch(prec_key){
        case SDL_SCANCODE_RIGHT:
            cur_sprite_ = sprite_[0 + animation];
            mv_x = speed;
            break;
        case SDL_SCANCODE_LEFT:
            cur_sprite_ = sprite_[2 + animation];
            mv_x = -speed;
            break;
        case SDL_SCANCODE_UP:
            cur_sprite_ = sprite_[4 + animation];
            mv_y = -speed;
            break;
        case SDL_SCANCODE_DOWN:
            cur_sprite_ = sprite_[6 + animation];
            mv_y = speed;
            break;
    }

    this->changePosition(position_.x + mv_x, position_.y + mv_y, map, bg);

}

void Ghost::chase(int animation, ThePacman *pacman ,std::vector<std::vector<Tile>> map, SDL_Rect bg){}

bool Ghost::intersection(float tailleCaseX,float tailleCaseY,std::vector<Tile> directions){

    // bien aligné sur une case => est ce qu'on est sur une intersection?
    int rondeur{4};
    int intersection{0};

    int cornerX=static_cast<int>((position_.x+rondeur)/tailleCaseX);
    int cornerXX=static_cast<int>((position_.x+position_.w-rondeur)/tailleCaseX);
    
    int cornerY=static_cast<int>(position_.y+rondeur)/tailleCaseY;
    int cornerYY=static_cast<int>(position_.y+position_.h-rondeur)/tailleCaseY;

    if(cornerX==cornerXX && cornerY==cornerYY){// aligné sur une case
        for( int i{0}; i<4 ;i++){
            if(directions[i]!=Tile::Wall && directions[i]!=Tile::GhostHouseDoor){// intersection
                intersection++;
            }
        }
    }

    if(intersection>=3){
        return true;
    }
    return false;
}

void Ghost::shortestPath(SDL_Rect *Goal,std::vector<Tile> directions,std::vector<std::vector<Tile>> map, SDL_Rect bg){
    // tailles d'une case de la carte
    float tailleCaseX = float(bg.w) / float(map[0].size());
    float tailleCaseY = float(bg.h) / float(map.size());

    // taille de la case du sprite
    int size = (position_.w );

    // origine = centre de la case du sprite et pas son coin gauche
    int origineX = position_.x + size/2;
    int origineY = position_.y + size/2;

    // origine = centre de la case du sprite et pas son coin gauche
    int GoalOrigineX = Goal->x + Goal->w/2;
    int GoalOrigineY = Goal->y + Goal->h/2;

    float min{(float)bg.h}; // distance min entre le goal et le ghost
    int best{5}; // meilleur direction possible

    for( int i{0}; i<4 ;i++){

        int nextX{origineX};
        int nextY{origineY};

        // on teste quelle direction est la meilleur
        if(directions[i]!=Tile::Wall && directions[i]!=Tile::GhostHouseDoor ){
            switch(i){
                case 0:
                    nextY=origineY+size;
                    break;
                case 1:
                    nextY=origineY-size;
                    break;
                case 2:
                    nextX=origineX+size;
                    break;
                case 3:
                    nextX=origineX-size;
                    break;
            }
            
            float dist=sqrt( pow(float(nextX-GoalOrigineX),2)+pow(float(nextY-GoalOrigineY),2));
            if(dist < min){
                min=dist;
                best=i;
            }
        }
    }
    switch(best){
        case 0:
            //std::cout<<"best:down"<<std::endl;
            prec_key=SDL_SCANCODE_DOWN;
            break;
        case 1:
            //std::cout<<"best:up"<<std::endl;
            prec_key=SDL_SCANCODE_UP;
            break;
        case 2:
            //std::cout<<"best:right"<<std::endl;
            prec_key=SDL_SCANCODE_RIGHT;
            break;
        case 3:
            //std::cout<<"best:left"<<std::endl;
            prec_key=SDL_SCANCODE_LEFT;
            break;
    }

}
