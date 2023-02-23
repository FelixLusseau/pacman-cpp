#include "../include/Character.hpp"
#include "../include/Map.hpp"

Character::Character(){};

void Character::changePosition(int x, int y, std::vector<std::vector<Tile>> map, SDL_Rect bg) {

    // tailles d'une case de la carte
    float tailleCaseX=float(bg.w)/float(map[0].size());
    float tailleCaseY=float(bg.h)/float(map.size());

    // taille de la case de pacman
    int tailleSprite=(position_.w/2);

    // origine = centre de la case de pacman et pas son coin gauche
    int origineX=position_.x+tailleSprite;
    int origineY=position_.y+tailleSprite;

    int ligne=origineX/tailleCaseX;
    int colonne=origineY/tailleCaseY;

    std::cout<<"vector: "<<ligne<<" "<<colonne<<" "<<std::endl;

    int futurX=x+tailleSprite;
    int futurY=y+tailleSprite;


   if(  (futurX<origineX  && map[futurY/tailleCaseY][(futurX-tailleSprite)/tailleCaseX]==Tile::Wall )      ||
        (futurY<origineY  && map[(futurY-tailleSprite)/tailleCaseY][futurX/tailleCaseX]==Tile::Wall )      ||
        (futurY>origineY  && map[(futurY+tailleSprite)/tailleCaseY][(futurX)/tailleCaseX]==Tile::Wall )    ||
        (futurX>origineX  && map[(futurY)/tailleCaseY][(futurX+tailleSprite)/tailleCaseX]==Tile::Wall )    ){
            return ;
    }

    position_.x = x;
    position_.y = y;

}