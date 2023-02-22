#include "../include/Character.hpp"
#include "../include/Map.hpp"

Character::Character(){};

void Character::changePosition(int x, int y, std::vector<std::vector<Tile>> map) {

    float tailleCase=float(664)/float(21);
    int tailleSprite=(position_.w/2)-2;

    int origineX=position_.x+tailleSprite;
    int origineY=position_.y+tailleSprite;

    int ligne=origineX/tailleCase;
    int colonne=origineY/tailleCase;

    std::cout<<"vector: "<<ligne<<" "<<colonne<<std::endl;

    int futurX=x+tailleSprite;
    int futurY=y+tailleSprite;


   if(  (futurX<origineX  && map[futurY/tailleCase][(futurX-tailleSprite)/tailleCase]==Tile::Wall )    ||
        (futurY<origineY  && map[(futurY-tailleSprite)/tailleCase][futurX/tailleCase]==Tile::Wall )    ||
        (futurY>origineY  && map[(futurY+tailleSprite)/tailleCase][(futurX)/tailleCase]==Tile::Wall )    ||
        (futurX>origineX  && map[(futurY)/tailleCase][(futurX+tailleSprite)/tailleCase]==Tile::Wall )    ){
            return ;
    }

    position_.x = x;
    position_.y = y;

}