#include "../include/Character.hpp"
#include "../include/Map.hpp"

Character::Character(){};

void Character::changePosition(int x, int y, std::vector<std::vector<Tile>> map) {
    int ligne=position_.x/34;
    int colonne=position_.y/34;

    std::cout<<"vector: "<<ligne<<" "<<colonne<<std::endl;

    // évite de sortir du cadre
    if( !(x<=168*4 && x>=0 && y<=216*4 && y>=0)){
        return ;
    }

    switch(map[y/34][x/34]){
        case Tile::Dot:
            std::cout<<"dot"<<std::endl;
            break;
        case Tile::PowerPellet:
            std::cout<<"PowerPellet"<<std::endl;
            break;
        case Tile::Empty:
            std::cout<<"Empty"<<std::endl;
            break;
    }

    if(map[y/34][x/34]==Tile::Wall){
        return ;
    }
    position_.x = x;
    position_.y = y;

}