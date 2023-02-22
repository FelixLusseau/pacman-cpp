#include "../include/Character.hpp"
#include "../include/Map.hpp"

Character::Character(){};

void Character::changePosition(int x, int y, std::vector<std::vector<Tile>> map) {
    float tailleCase=float(664)/float(21);
    std::cout<<tailleCase<<std::endl;
    int ligne=x/tailleCase;
    int colonne=y/tailleCase;

    std::cout<<"vector: "<<ligne<<" "<<colonne<<std::endl;

    /* évite de sortir du cadre
    if( !(x<=714 && x>=0 && y<=918 && y>=0)){
        return ;
    }*/


   if( ((x<position_.x || y<position_.y ) && map[y/tailleCase][x/tailleCase]==Tile::Wall )    ||
        (y>position_.y  && map[(y+32)/tailleCase][(x+2)/tailleCase]==Tile::Wall )    ||
        (x>position_.x  && map[(y+2)/tailleCase][(x+32)/tailleCase]==Tile::Wall )    ){
            return ;
    }

    position_.x = x;
    position_.y = y;

}